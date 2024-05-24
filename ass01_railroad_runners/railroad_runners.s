################################################################################
# COMP1521 24T1 -- Assignment 1 -- Railroad Runners!
#
#
# !!! IMPORTANT !!!
# Before starting work on the assignment, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
# Instructions to configure your text editor can be found here:
#   https://cgi.cse.unsw.edu.au/~cs1521/24T1/resources/mips-editors.html
# !!! IMPORTANT !!!
#
#
# This program was written by YOUR-NAME-HERE (z5555555)
# on INSERT-DATE-HERE
#
# Version 1.0 (2024-02-27): Team COMP1521 <cs1521@cse.unsw.edu.au>
#
################################################################################

#![tabsize(8)]

# ------------------------------------------------------------------------------
#                                   Constants
# ------------------------------------------------------------------------------

# -------------------------------- C Constants ---------------------------------
TRUE = 1
FALSE = 0

JUMP_KEY = 'w'
LEFT_KEY = 'a'
CROUCH_KEY = 's'
RIGHT_KEY = 'd'
TICK_KEY = '\''
QUIT_KEY = 'q'

ACTION_DURATION = 3
CHUNK_DURATION = 10

SCROLL_SCORE_BONUS = 1
TRAIN_SCORE_BONUS = 1
BARRIER_SCORE_BONUS = 2
CASH_SCORE_BONUS = 3

MAP_HEIGHT = 20
MAP_WIDTH = 5
PLAYER_ROW = 1

PLAYER_RUNNING = 0
PLAYER_CROUCHING = 1
PLAYER_JUMPING = 2

STARTING_COLUMN = MAP_WIDTH / 2

TRAIN_CHAR = 't'
BARRIER_CHAR = 'b'
CASH_CHAR = 'c'
EMPTY_CHAR = ' '
WALL_CHAR = 'w'
RAIL_EDGE = '|'

SAFE_CHUNK_INDEX = 0
NUM_CHUNKS = 14

# --------------------- Useful Offset and Size Constants -----------------------

# struct BlockSpawner offsets
BLOCK_SPAWNER_NEXT_BLOCK_OFFSET = 0
BLOCK_SPAWNER_SAFE_COLUMN_OFFSET = 20
BLOCK_SPAWNER_SIZE = 24

# struct Player offsets
PLAYER_COLUMN_OFFSET = 0
PLAYER_STATE_OFFSET = 4
PLAYER_ACTION_TICKS_LEFT_OFFSET = 8
PLAYER_ON_TRAIN_OFFSET = 12
PLAYER_SCORE_OFFSET = 16
PLAYER_SIZE = 20

SIZEOF_PTR = 4


# ------------------------------------------------------------------------------
#                                 Data Segment
# ------------------------------------------------------------------------------
	.data

# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE DEFINITIONS !!!

# ----------------------------- String Constants -------------------------------

print_welcome__msg_1:
	.asciiz "Welcome to Railroad Runners!\n"
print_welcome__msg_2_1:
	.asciiz "Use the following keys to control your character: ("
print_welcome__msg_2_2:
	.asciiz "):\n"
print_welcome__msg_3:
	.asciiz ": Move left\n"
print_welcome__msg_4:
	.asciiz ": Move right\n"
print_welcome__msg_5_1:
	.asciiz ": Crouch ("
print_welcome__msg_5_2:
	.asciiz ")\n"
print_welcome__msg_6_1:
	.asciiz ": Jump ("
print_welcome__msg_6_2:
	.asciiz ")\n"
print_welcome__msg_7_1:
	.asciiz "or press "
print_welcome__msg_7_2:
	.asciiz " to continue moving forward.\n"
print_welcome__msg_8_1:
	.asciiz "You must crouch under barriers ("
print_welcome__msg_8_2:
	.asciiz ")\n"
print_welcome__msg_9_1:
	.asciiz "and jump over trains ("
print_welcome__msg_9_2:
	.asciiz ").\n"
print_welcome__msg_10_1:
	.asciiz "You should avoid walls ("
print_welcome__msg_10_2:
	.asciiz ") and collect cash ("
print_welcome__msg_10_3:
	.asciiz ").\n"
print_welcome__msg_11:
	.asciiz "On top of collecting cash, running on trains and going under barriers will get you extra points.\n"
print_welcome__msg_12_1:
	.asciiz "When you've had enough, press "
print_welcome__msg_12_2:
	.asciiz " to quit. Have fun!\n"

get_command__invalid_input_msg:
	.asciiz "Invalid input!\n"

main__game_over_msg:
	.asciiz "Game over, thanks for playing 😊!\n"

display_game__score_msg:
	.asciiz "Score: "

handle_collision__barrier_msg:
	.asciiz "💥 You ran into a barrier! 😵\n"
handle_collision__train_msg:
	.asciiz "💥 You ran into a train! 😵\n"
handle_collision__wall_msg:
	.asciiz "💥 You ran into a wall! 😵\n"

maybe_pick_new_chunk__column_msg_1:
	.asciiz "Column "
maybe_pick_new_chunk__column_msg_2:
	.asciiz ": "
maybe_pick_new_chunk__safe_msg:
	.asciiz "New safe column: "

get_seed__prompt_msg:
	.asciiz "Enter a non-zero number for the seed: "
get_seed__prompt_invalid_msg:
	.asciiz "Invalid seed!\n"
get_seed__set_msg:
	.asciiz "Seed set to "

TRAIN_SPRITE:
	.asciiz "🚆"
BARRIER_SPRITE:
	.asciiz "🚧"
CASH_SPRITE:
	.asciiz "💵"
EMPTY_SPRITE:
	.asciiz "  "
WALL_SPRITE:
	.asciiz "🧱"

PLAYER_RUNNING_SPRITE:
	.asciiz "🏃"
PLAYER_CROUCHING_SPRITE:
	.asciiz "🧎"
PLAYER_JUMPING_SPRITE:
	.asciiz "🤸"

# ------------------------------- Chunk Layouts --------------------------------

SAFE_CHUNK: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
CHUNK_1: # char[]
	.byte EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, WALL_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, BARRIER_CHAR, '\0',
CHUNK_2: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_3: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_4: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_5: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, EMPTY_CHAR, TRAIN_CHAR, EMPTY_CHAR, EMPTY_CHAR, '\0',
CHUNK_6: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, BARRIER_CHAR, EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, CASH_CHAR, EMPTY_CHAR, BARRIER_CHAR, '\0'
CHUNK_7: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, '\0',
CHUNK_8: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, CASH_CHAR, EMPTY_CHAR, '\0',
CHUNK_9: # char[]
	.byte CASH_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_10: # char[]
	.byte CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, CASH_CHAR, '\0',
CHUNK_11: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, WALL_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, TRAIN_CHAR, '\0',
CHUNK_12: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, CASH_CHAR, '\0',
CHUNK_13: # char[]
	.byte EMPTY_CHAR, EMPTY_CHAR, EMPTY_CHAR, WALL_CHAR, WALL_CHAR, '\0',

CHUNKS:	# char*[]
	.word SAFE_CHUNK, CHUNK_1, CHUNK_2, CHUNK_3, CHUNK_4, CHUNK_5, CHUNK_6, CHUNK_7, CHUNK_8, CHUNK_9, CHUNK_10, CHUNK_11, CHUNK_12, CHUNK_13

# ----------------------------- Global Variables -------------------------------

g_block_spawner: # struct BlockSpawner
	# char *next_block[MAP_WIDTH], offset 0
	.word 0, 0, 0, 0, 0
	# int safe_column, offset 20
	.word STARTING_COLUMN

g_map: # char[MAP_HEIGHT][MAP_WIDTH]
	.space MAP_HEIGHT * MAP_WIDTH

g_player: # struct Player
	# int column, offset 0
	.word STARTING_COLUMN
	# int state, offset 4
	.word PLAYER_RUNNING
	# int action_ticks_left, offset 8
	.word 0
	# int on_train, offset 12
	.word FALSE
	# int score, offset 16
	.word 0

g_rng_state: # unsigned
	.word 1

# !!! Reminder to not not add to or modify any of the above !!!
# !!! strings or any other part of the data segment.        !!!

# ------------------------------------------------------------------------------
#                                 Text Segment
# ------------------------------------------------------------------------------
	.text

############################################################
####                                                    ####
####   Your journey begins here, intrepid adventurer!   ####
####                                                    ####
############################################################

################################################################################
#
# Implement the following functions,
# and check these boxes as you finish implementing each function.
#
#  SUBSET 0
#  - [ ] print_welcome
#  SUBSET 1
#  - [ ] get_command
#  - [ ] main
#  - [ ] init_map
#  SUBSET 2
#  - [ ] run_game
#  - [ ] display_game
#  - [ ] maybe_print_player
#  - [ ] handle_command
#  SUBSET 3
#  - [ ] handle_collision
#  - [ ] maybe_pick_new_chunk
#  - [ ] do_tick
#  PROVIDED
#  - [X] get_seed
#  - [X] rng
#  - [X] read_char
################################################################################

################################################################################
# .TEXT <print_welcome>
print_welcome:
	# Subset:   0
	#
	# Args:     None
	#
	# Returns:  None
	#
	# Frame:    []
	# Uses:     [$v0, $a0]
	# Clobbers: [$v0, $a0]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   print_welcome
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

print_welcome__prologue:
print_welcome__body:
	# TODO: implement `print_welcome` here!


	li $v0, 4  # printf("Welcome to Railroad Runners!\n");
	li $a0, print_welcome__msg_1
	syscall

	li $v0, 4 # printf("Use the following keys to control your character: (%s):\n", PLAYER_RUNNING_SPRITE);
	li $a0, print_welcome__msg_2_1
	syscall

	li $v0, 4
	li $a0, PLAYER_RUNNING_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_2_2
	syscall

	li $v0, 11 # printf("%c: Move left\n", LEFT_KEY);
	li $a0, LEFT_KEY
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_3
	syscall

	li $v0, 11 # printf("%c: Move right\n", RIGHT_KEY);
	li $a0, RIGHT_KEY
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_4
	syscall

	li $v0, 11 # printf("%c: Crouch (%c)\n", CROUCH_KEY, PLAYER_CROUCHING_SPRITE);
	li $a0, CROUCH_KEY
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_5_1
	syscall

	li $v0, 4
	li $a0, PLAYER_CROUCHING_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_5_2
	syscall

	li $v0, 11 # printf("%c: Jump (%c)\n", JUMP_KEY, PLAYER_JUMPING_SPRITE);
	li $a0, JUMP_KEY
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_6_1
	syscall

	li $v0, 4
	li $a0, PLAYER_JUMPING_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_6_2
	syscall

	li $v0, 4 # printf("or press %c to continue moving forward.\n", TICK_KEY);
	li $a0, print_welcome__msg_7_1
	syscall

	li $v0, 11
	li $a0, TICK_KEY
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_7_2
	syscall

	li $v0, 4 # printf("You must crouch under barriers (%s)\n", BARRIER_SPRITE);
	li $a0, print_welcome__msg_8_1
	syscall

	li $v0, 4
	li $a0, BARRIER_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_8_2
	syscall

	li $v0, 4 # printf("and jump over trains (%s).\n", TRAIN_SPRITE);
	li $a0, print_welcome__msg_9_1
	syscall

	li $v0, 4
	li $a0, TRAIN_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_9_2
	syscall

	li $v0, 4 # printf("You should avoid walls (%s) and collect cash (%s).\n", WALL_SPRITE, CASH_SPRITE);
	li $a0, print_welcome__msg_10_1
	syscall

	li $v0, 4
	li $a0, WALL_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_10_2
	syscall

	li $v0, 4
	li $a0, CASH_SPRITE
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_10_3
	syscall

	li $v0, 4 # printf("On top of collecting cash, running on trains and going under barriers will get you extra points.\n");
	li $a0, print_welcome__msg_11
	syscall

	li $v0, 4 # printf("When you've had enough, press %c to quit. Have fun!\n", QUIT_KEY);
	li $a0, print_welcome__msg_12_1
	syscall

	li $v0, 11
	li $a0, QUIT_KEY
	syscall

	li $v0, 4
	li $a0, print_welcome__msg_12_2
	syscall

print_welcome__epilogue:
	jr	$ra


################################################################################
# .TEXT <get_command>
	.text
get_command:
	# Subset:   1
	#
	# Args:     None
	#
	# Returns:  $v0: char
	#
	# Frame:    [[read_char]]
	# Uses:     [$t0, $v0, $a0]
	# Clobbers: [$t0, $v0, $a0]
	#
	# Locals:
	#   - $t0 = char input
	#
	# Structure:
	#   get_command
	#   -> [prologue]
	#     -> body
	#     -> while_start
	#     -> while__if_then
	#   -> [epilogue]

get_command__prologue:
get_command__body:

get_command__while_start:
	begin 							# char input = read_char();
	push $ra
	jal read_char
	pop $ra
	end

	move $t0, $v0

								# if (input == QUIT_KEY || input == JUMP_KEY || input == LEFT_KEY ||
								#     input == CROUCH_KEY || input == RIGHT_KEY || input == TICK_KEY) {
								#     return input;
								# }
	beq $t0, QUIT_KEY, get_command__while__if_then
	beq $t0, JUMP_KEY, get_command__while__if_then
	beq $t0, LEFT_KEY, get_command__while__if_then
	beq $t0, CROUCH_KEY, get_command__while__if_then
	beq $t0, RIGHT_KEY, get_command__while__if_then
	beq $t0, TICK_KEY, get_command__while__if_then

	li $v0, 4 						# printf("Invalid input!\n");
	la $a0, get_command__invalid_input_msg
	syscall

	j get_command__while_start
get_command__while__if_then:
	move $v0, $t0
	j get_command__epilogue

get_command__epilogue:
	jr	$ra


################################################################################
# .TEXT <main>
	.text
main:
	# Subset:   1
	#
	# Args:     None
	#
	# Returns:  $v0: int
	#
	# Frame:    [[print_welcome],[get_seed],[init_map],[display_game],[run_game]]
	# Uses:     [$ra, $a0, $a1, $a2, $a3, $v0]
	# Clobbers: [$ra, $a0, $a1, $a2, $a3, $v0]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   main
	#   -> [prologue]
	#     -> body
	#     -> do_while_do
	#     -> do_while_condition
	#   -> [epilogue]

main__prologue:
main__body:
	push $ra

	jal print_welcome # print_welcome();
	jal get_seed # get_seed();

	la $a0, g_map # init_map(g_map);
	jal init_map

main__do_while_do:
	la $a0, g_map # display_game(g_map, &g_player);
	la $a1, g_player
	jal display_game
mani__do_while_condition:
	jal get_command  # run_game(g_map, &g_player, &g_block_spawner, get_command());
	move $a3, $v0

	la $a0, g_map
	la $a1, g_player
	la $a2, g_block_spawner
	jal run_game

	beqz $v0, main__do_while_end # while (run_game(...) == 0) {}
	j main__do_while_do
main__do_while_end:

	li $v0, 4
	la $a0, main__game_over_msg
	syscall

main__epilogue:
	pop $ra
	li $v0, 0
	jr	$ra


################################################################################
# .TEXT <init_map>
	.text
init_map:
	# Subset:   1
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [$t0, $t1, $t2, $t3]
	# Clobbers: [$t0, $t1, $t2, $t3]
	#
	# Locals:
	#   - $t0 = int i
	#   - $t1 = int j
	#   - $t2 = calculated offset
	#   - $t3 = calculated offset, char value
	#
	# Structure:
	#   init_map
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

init_map__prologue:
init_map__body:

init_map__for1_init:
	li $t0, 0 				# for(int i = 0; ...)
init_map__for1_condition:
	blt $t0, MAP_HEIGHT, init_map__for1_body
	j init_map__for1_end
init_map__for1_body:

init_map__for2_init:
	li $t1, 0 				# for(int j = 0; ...)
init_map__for2_condition:
	blt $t1, MAP_WIDTH, init_map__for2_body
	j init_map__for2_end
init_map__for2_body:
	mul $t2, $t0, MAP_WIDTH 		# i * row_length
	mul $t2, $t2, 1				# i * row_length * sizeof(char)
	mul $t3, $t1, 1 			# j * sizeof(char)
	add $t2, $t2, $t3 			# i * row_length * sizeof(char) + j * sizeof(char)
	add $t2, $a0, $t2 			# map + ...

	li $t3, EMPTY_CHAR
	sb $t3, ($t2) 				# map[i][j] = EMPTY_CHAR;
	
init_map__for2_iter:
	add $t1, $t1, 1
	j init_map__for2_condition
init_map__for2_end:

init_map__for1_iter:
	add $t0, $t0, 1
	j init_map__for1_condition
init_map__for1_end:

        # $t0 - $t3 are free to use
	# $t0 = row offset
	# $t1 = overall offset
	# $t2 = char value

	li $t0, 6 			# 6 * row_length * sizeof(char)
	mul $t0, $t0, MAP_WIDTH
	mul $t0, $t0, 1

	add $t1, $a0, $t0		# map[6][0] = WALL_CHAR;
	li $t2, WALL_CHAR
	sb $t2, ($t1)

	add $t1, $t1, 1 		# map[6][1] = TRAIN_CHAR;
	li $t2, TRAIN_CHAR
	sb $t2, ($t1)

	add $t1, $t1, 1 		# map[6][2] = CAHS_CHAR;
	li $t2, CASH_CHAR
	sb $t2, ($t1)

	add $t1, $t1, 10 		# map[8][2] = BARIRER_CHAR;
	li $t2, BARRIER_CHAR
	sb $t2, ($t1)

init_map__epilogue:
	jr	$ra


################################################################################
# .TEXT <run_game>
	.text
run_game:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#   - $a3: char input
	#
	# Returns:  $v0: int
	#
	# Frame:    [[handle_command],[handle_collision]]
	# Uses:     [$ra, $a0, $a1, $a2, $a3, $v0]
	# Clobbers: [$ra, $a0, $a1, $a2, $a3, $v0]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   run_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

run_game__prologue:
run_game__body:
	
	beq $a3, QUIT_KEY, run_game__if_then 	# if (input == QUIT_KEY)
	j run_game__if_end
run_game__if_then:
	li $v0, FALSE
	jr $ra 					# return FALSE
run_game__if_end:

	push $ra

	push $a0
	push $a1
	jal handle_command 			# handle_command(map, player, block_spawner, input)
	pop $a1
	pop $a0
	
	jal handle_collision 			# handle_collision(map, player)
	
	pop $ra

run_game__epilogue:
	jr	$ra


################################################################################
# .TEXT <display_game>
	.text
display_game:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#
	# Returns:  None
	#
	# Frame:    [[maybe_print_player]]
	# Uses:     [$ra, $s0, $s1, $t0, $t1, $t2, $t3, $v0]
	# Clobbers: [$ra, $s0, $s1, $t0, $t1, $t2, $t3, $v0]
	#
	# Locals:
	#   - $t0 = int i
	#   - $t1 = int j
	#   - $t2 = array offset
	#   - $t3 = map_char
	#   - $s0 = map
	#   - $s1 = player
	#
	# Structure:
	#   display_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

display_game__prologue:
display_game__body:

	push $ra
	push $s0
	push $s1
	move $s0, $a0
	move $s1, $a1

display_game__for1_init:
	li $t0, MAP_HEIGHT
	addi $t0, -1
display_game__for1_condition:
	bge $t0, 0, display_game__for1_body # for(int i = MAP_HEIGHT - 1; ...)
	j display_game__for1_end
display_game__for1_body:

display_game__for2_init:
	li $t1, 0 				# for(int j = 0; ...)
display_game__for2_condition:
	blt $t1, MAP_WIDTH, display_game__for2_body
	j display_game__for2_end
display_game__for2_body:
	li $v0, 11 				# putchar(RAIL_EDGE)
	la $a0, RAIL_EDGE
	syscall


	push $t0
	push $t1
	
	move $a0, $s1
	move $a1, $t0
	move $a2, $t1
	jal maybe_print_player 			# if (!maybe_print_player(player, i, j))
	not $v0, $v0				# 0001 will become 1110
	andi $v0, $v0, 1			# 1110 will become 0000

	pop $t1
	pop $t0


	beqz $v0, display_game__for2__if_end
	j display_game__for2__if_then
display_game__for2__if_then:
	mul $t2, $t0, MAP_WIDTH			 # i * row_length
	add $t2, $t2, $t1			 # i * row_length + j
	add $t2, $t2, $s0 			 # ... + map

	lb $t3, ($t2)				 # map_char = map[i][j]

	bne $t3, EMPTY_CHAR, not_empty   # if (map_char == EMPTY_CHAR)
	li $v0, 4
	la $a0, EMPTY_SPRITE
	syscall
not_empty:
	bne $t3, BARRIER_CHAR, not_barrier_char # else if (map_char == BARRIER_CHAR)
	li $v0, 4
	la $a0, BARRIER_SPRITE
	syscall
not_barrier_char:
	bne $t3, TRAIN_CHAR, not_train_char # else if (map_char == TRAIN_CHAR)
	li $v0, 4
	la $a0, TRAIN_SPRITE
	syscall
not_train_char:
	bne $t3, CASH_CHAR, not_cash_char # else if (map_char == CASH_CHAR)
	li $v0, 4
	la $a0, CASH_SPRITE
	syscall
not_cash_char:
	bne $t3, WALL_CHAR, not_wall_char # else if (map_char == WALL_CHAR)
	li $v0, 4
	la $a0, WALL_SPRITE
	syscall
not_wall_char:

display_game__for2__if_end:
	li $v0, 11				 # putchar(RAIL_EDGE)
	la $a0, RAIL_EDGE
	syscall
display_game__for2_iter:
	add $t1, $t1, 1
	j display_game__for2_condition
display_game__for2_end:

	li $v0, 11 				# putchar('\n')
	la $a0, '\n'
	syscall
display_game__for1_iter:
	addi $t0, -1
	j display_game__for1_condition
display_game__for1_end:

	li $v0, 4 				# printf("Score: %d\n", player->score);
	la $a0, display_game__score_msg
	syscall

	li $v0, 1
	lw $a0, PLAYER_SCORE_OFFSET($s1)
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall

display_game__epilogue:
	pop $s1
	pop $s0
	pop $ra
	li $v0, 0
	jr	$ra


################################################################################
# .TEXT <maybe_print_player>
	.text
maybe_print_player:
	# Subset:   2
	#
	# Args:
	#   - $a0: struct Player *player
	#   - $a1: int row
	#   - $a2: int column
	#
	# Returns:  $v0: int
	#
	# Frame:    [...]
	# Uses:     [$ra, $s0, $s1, $s2, $t0]
	# Clobbers: [$ra, $s0, $s1, $s2, $t0]
	#
	# Locals:
	#   - $s0 = player
	#   - $s1 = row
	#   - $s2 = column
	#   - $t0 = player_column, player_state
	#
	# Structure:
	#   maybe_print_player
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_print_player__prologue:
maybe_print_player__body:
        push $ra
	push $s0
	push $s1
	push $s2
	move $s0, $a0
	move $s1, $a1
	move $s2, $a2

	beq $s0, 0, maybe_print_player__if1_then 	 	# if (player == NULL)

	lw $t0, PLAYER_COLUMN_OFFSET($s0) 		 	# int column = player->column
	bne $s1, PLAYER_ROW, maybe_print_player__if1_then	# if (row != PLAYER_ROW)
	bne $s2, $t0, maybe_print_player__if1_then  	 	# if (column != player->column)
	j maybe_print_player__if1_end
maybe_print_player__if1_then:
	li $v0, FALSE 						# return FALSE
	j maybe_print_player__epilogue
maybe_print_player__if1_end:

	lw $t0, PLAYER_STATE_OFFSET($s0) 			# int state = player->state

	bne $t0, PLAYER_RUNNING, not_running			# if (state == PLAYER_RUNNING)
	li $v0, 4
	la $a0, PLAYER_RUNNING_SPRITE
	syscall
not_running:
	bne $t0, PLAYER_CROUCHING, not_crouching 		# else if (state == PLAYER_CROUCHING)
	li $v0, 4
	la $a0, PLAYER_CROUCHING_SPRITE
	syscall
not_crouching:
	bne $t0, PLAYER_JUMPING, not_jumping 			# else if (state == PLAYER_JUMPING)
	li $v0, 4
	la $a0, PLAYER_JUMPING_SPRITE
	syscall
not_jumping:

	li $v0, TRUE 						# return TRUE
	j maybe_print_player__epilogue

maybe_print_player__epilogue:
	pop $s2
	pop $s1
	pop $s0
	pop $ra
	jr	$ra


################################################################################
# .TEXT <handle_command>
	.text
handle_command:
	# Subset:   2
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#   - $a3: char input
	#
	# Returns:  None
	#
	# Frame:    [[do_tick]]
	# Uses:     [$ra, $s0, $s1, $s2, $s3, $t0, $t1, $t8]
	# Clobbers: [$t0, $t1, $t8]
	#
	# Locals:
	#   - $s0 = map
	#   - $s1 = player
	#   - $s2 = block_spawner
	#   - $s3 = input
	#   - $t0 = player->column
	#   - $t1 = player->state
	#   - $t8 = temporary
	#
	# Structure:
	#   handle_command
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_command__prologue:
handle_command__body:
	push $s0
	push $s1
	push $s2
	push $s3
	push $ra
	move $s0, $a0
	move $s1, $a1
	move $s2, $a2
	move $s3, $a3

	lw $t0, PLAYER_COLUMN_OFFSET($s1) 		# int = player->column
	lw $t1, PLAYER_STATE_OFFSET($s1) 		# int = player->state

	bne $s3, LEFT_KEY, not_left_key 		# if (input == LEFT_KEY)
	blez $t0, not_left_key 				# if (player->column > 0)

	move $t8, $t0 					# --player->column
	sub $t8, $t8, 1
	sw $t8, PLAYER_COLUMN_OFFSET($s1)
not_left_key:

	bne $s3, RIGHT_KEY, not_right_key 		# if (input == RIGHT_KEY)
	bge $t0, MAP_WIDTH - 1, not_right_key 		# if (player->column < MAP_WIDTH - 1)

	move $t8, $t0 					# ++player->column
	addi $t8, $t8, 1
	sw $t8, PLAYER_COLUMN_OFFSET($s1)
not_right_key:

	bne $s3, JUMP_KEY, not_jump_key 		# if (input == JUMP_KEY)
	bne $t1, PLAYER_RUNNING, not_jump_key 		# if (player->state == PLAYER_RUNNING)

	li $t8, PLAYER_JUMPING 				# player->state = PLAYER_JUMPING
	sw $t8, PLAYER_STATE_OFFSET($s1)
	li $t8, ACTION_DURATION 			# player->action_ticks_left = ACTION_DURATION
	sw $t8, PLAYER_ACTION_TICKS_LEFT_OFFSET($s1)
not_jump_key:

	bne $s3, CROUCH_KEY, not_crouch_key 		# if (input == CROUCH_KEY)
	bne $t1, PLAYER_RUNNING, not_crouch_key 	# if (player->state == PLAYER_RUNNING)

	li $t8, PLAYER_CROUCHING 			# player->state = PLAYER_CROUCHING
	sw $t8, PLAYER_STATE_OFFSET($s1)
	li $t8, ACTION_DURATION 			# player->action_ticks_left = ACTION_DURATION
	sw $t8, PLAYER_ACTION_TICKS_LEFT_OFFSET($s1)
not_crouch_key:

	bne $s3, TICK_KEY, not_tick_key 		# if (input == TICK_KEY)

	move $a0, $s0
	move $a1, $s1
	move $a2, $s2
	jal do_tick 					# do_tick(map, player, block_spawner)
not_tick_key:

handle_command__epilogue:
	pop $ra
	pop $s3
	pop $s2
	pop $s1
	pop $s0
	li $v0, 0
	jr $ra


################################################################################
# .TEXT <handle_collision>
	.text
handle_collision:
	# Subset:   3
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#
	# Returns:  $v0: int
	#
	# Frame:    []
	# Uses:     [$ra, $s0, $s1, $s2, $a0, $t0, $t1]
	# Clobbers: [$t0, $t1, $a0]
	#
	# Locals:
	#   - $s0 = map
	#   - $s1 = player
	#   - $s2 = char *map_char
	#
	# Structure:
	#   handle_collision
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_collision__prologue:
handle_collision__body:
	push $ra
	push $s0
	push $s1
	push $s2
	move $s0, $a0
	move $s1, $a1
	
	# get player->column, player->state, player->score, player->on_train

	li $t0, MAP_WIDTH
	mul $t0, $t0, PLAYER_ROW 		# player->row * row_length
	lw $t1, PLAYER_COLUMN_OFFSET($s1) 	# player->column
	add $t0, $t0, $t1 			# player->row * row_length + player->column
	add $t0, $t0, $s0 			# ... + map
	move $s2, $t0 				# map_char = &map[PLAYER_ROW][player->column]


	lb $t0, ($s2) 				# $t0 = *map_char
	bne $t0, BARRIER_CHAR, handle_collision__not_barrier_char # if (*map_char == BARRIER_CHAR)

	lw $t0, PLAYER_STATE_OFFSET($s1) 	# int state = player->state
	bne $t0, PLAYER_CROUCHING, handle_collision__is_barrier_char__is_not_crouching # if (player->state != PLAYER_CROUCHING)
	j handle_collision__is_barrier_char__is_crouching
handle_collision__is_barrier_char__is_crouching:
	lw $t0, PLAYER_SCORE_OFFSET($s1)
	addi $t0, $t0, BARRIER_SCORE_BONUS
	sw $t0, PLAYER_SCORE_OFFSET($s1)	# player->score += score
	j handle_collision__not_barrier_char
handle_collision__is_barrier_char__is_not_crouching:
	li $v0, 4 				# printf("💥 You ran into a barrier! 😵\n");
	la $a0, handle_collision__barrier_msg
	syscall

	li $v0, FALSE 				# return FALSE
	j handle_collision__epilogue
handle_collision__not_barrier_char:


	lb $t0, ($s2) 				# $t0 = *map_char
	beq $t0, TRAIN_CHAR, handle_collision__is_train_char # if (*map_char == TRAIN_CHAR)
	j handle_collision__not_train_char
handle_collision__is_train_char:

	lw $t0, PLAYER_STATE_OFFSET($s1) 	# int state = player->state
	beq $t0, PLAYER_JUMPING, handle_collision__not_ran_into_a_train
	lw $t0, PLAYER_ON_TRAIN_OFFSET($s1) 	# int on_train = player->on_train
	bnez $t0, handle_collision__not_ran_into_a_train

	li $v0, 4 				# printf("💥 You ran into a train! 😵\n");
	la $a0, handle_collision__train_msg
	syscall

	li $v0, FALSE 				# return FALSE
	j handle_collision__epilogue
handle_collision__not_ran_into_a_train:

	li $t0, TRUE 				# player->on_train = TRUE
	sw $t0, PLAYER_ON_TRAIN_OFFSET($s1)

	lw $t0, PLAYER_STATE_OFFSET($s1) 	# int state = player->state
	beq $t0, PLAYER_JUMPING, handle_collision__is_jumping

	lw $t0, PLAYER_SCORE_OFFSET($s1)
	addi $t0, TRAIN_SCORE_BONUS
	sw $t0, PLAYER_SCORE_OFFSET($s1) 	# player->score += score
handle_collision__is_jumping:
	j handle_collision__is_train_char_end

handle_collision__not_train_char:
	li $t0, FALSE 				# player->on_train = FALSE
	sw $t0, PLAYER_ON_TRAIN_OFFSET($s1)
handle_collision__is_train_char_end:

	lb $t0, ($s2) 				# $t0 = *map_char
	bne $t0, WALL_CHAR, handle_collision__not_wall_char # if (*map_char == WALL_CHAR)

	# is wall_char
	li $v0, 4 				# printf("💥 You ran into a wall! 😵\n");
	la $a0, handle_collision__wall_msg
	syscall

	li $v0, FALSE 				# return FALSE
	j handle_collision__epilogue
handle_collision__not_wall_char:

	lb $t0, ($s2) 				# $t0 = *map_char
	bne $t0, CASH_CHAR, handle_collision__not_cash_char # if (*map_char == CASH_CHAR)

	# is cash_char
	lw $t0, PLAYER_SCORE_OFFSET($s1)	 # player->score += score 	
	addi $t0, CASH_SCORE_BONUS 		
	sw $t0, PLAYER_SCORE_OFFSET($s1)

	li $t0, EMPTY_CHAR 			# *map_char = EMPTY_CHAR
	sb $t0, ($s2)
handle_collision__not_cash_char:

	li $v0, TRUE 				# return TRUE
	
handle_collision__epilogue:
	pop $s2
	pop $s1
	pop $s0
	pop $ra
	jr	$ra


################################################################################
# .TEXT <maybe_pick_new_chunk>
	.text
maybe_pick_new_chunk:
	# Subset:   3
	#
	# Args:
	#   - $a0: struct BlockSpawner *block_spawner
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - $s0 = block_spawner
	#   - $t8 = new_safe_column_required
	#   - $t7 = int column
	#   - $t6 = char const **next_block_ptr
	#
	# Structure:
	#   maybe_pick_new_chunk
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_pick_new_chunk__prologue:
maybe_pick_new_chunk__body:
	push $ra
	push $s0
	move $s0, $a0

	li $t8, FALSE

m__for_init:
	li $t7, 0
m__for_condition:
	blt $t7, MAP_WIDTH, m__for_body
	j m__for_end
m__for_body:

# for body start
	lw $t0,	BLOCK_SPAWNER_NEXT_BLOCK_OFFSET($s0) 	# block_spawner->next_block
	li $t1, 4
	mul $t1, $t1, $t7				# column * sizeof(char*)

	# debug code
	beqz $t0, error
	beqz $t1, error
	j not_error
error:
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 1
	move $a0, $t1
	syscall
	j maybe_pick_new_chunk__epilogue
not_error:

	add $t0, $t0, $t1 				# block_spawner->next_block + column * sizeof(char*)
	move $t6, $t0


	# if (*next_block_ptr && **next_block_ptr)
	lw $t0, ($t6)
	beqz $t0, m__for__if_not_continue
	lw $t0, ($t0)
	beqz $t0, m__for__if_not_continue
m__for__if_continue:
	j m__for_iter
m__for__if_not_continue:

	# $t0 = chunk
	push $t0
	push $t1
	push $t2
	push $a0
	jal rng
	pop $a0
	pop $t2
	pop $t1
	pop $t0
	remu $t0, $v0, NUM_CHUNKS

	li $v0, 4
	la $a0, maybe_pick_new_chunk__column_msg_1
	syscall

	li $v0, 1
	move $a0, $t7
	syscall

	li $v0, 4
	la $a0, maybe_pick_new_chunk__column_msg_2
	syscall

	li $v0, 1
	move $a0, $t0
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall # printf("Column: %d, Chunk: %d\n", column, chunk);

	# $t0 free to use

	mul $t0, $t0, 4 # chunk * sizeof(char*)
	addi $t0, $t0, CHUNKS
	lw $t1, ($t0)  # $t1 is to be saved in *next_block_ptr

	lw $t0, ($t6)  # $t0 = *next_block_ptr
	sw $t1, ($t0)  # *next_block_ptr = CHUNKS[chunk]

	# if (column == block_spawner->safe_column)
	lw $t0, BLOCK_SPAWNER_SAFE_COLUMN_OFFSET($s0)
	beq $t7, $t0, m__for__if_is_safe_column
	j m__for__if_not_safe_column
m__for__if_is_safe_column:
	li $t8, TRUE
m__for__if_not_safe_column:

# for body end
	
m__for_iter:
	addi $t7, $t7, 1 # ++column
	j m__for_condition
m__for_end:


	# if (new_safe_column_required)
	beqz $t8, m__if_not_new_safe_column_required
	j m__if_new_safe_column_required
m__if_new_safe_column_required:
	# $t0 = safe_column
	push $t0
	push $t1
	push $t2
	push $a0
	jal rng
	pop $a0
	pop $t2
	pop $t1
	pop $t0
	remu $t0, $v0, MAP_WIDTH

	li $v0, 4
	la $a0, maybe_pick_new_chunk__safe_msg
	syscall

	li $v0, 1
	move $a0, $t0
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall 					# printf("New safe column: %d\n", safe_column);

	sw $t0, BLOCK_SPAWNER_SAFE_COLUMN_OFFSET($s0) 	# block_spawner->safe_column = safe_column;



	li $t3, 4					# block_spawner->next_block[safe_column] = CHUNKS[SAFE_CHUNK_INDEX];
	mul $t3, $t3, $t0
	add $t3, $t3, $s0
	add $t3, $t3, BLOCK_SPAWNER_NEXT_BLOCK_OFFSET

	lw $t1, CHUNKS
	sw $t1, ($t3)

	# $t0 free to use

	#debug
	beqz $s0, error2
	j not_error2
error2:
	li $v0, 1
	move $a0, $s0
	syscall
	li $v0, 1
	move $a0, $t1
	syscall
	j maybe_pick_new_chunk__epilogue
not_error2:


m__if_not_new_safe_column_required:


maybe_pick_new_chunk__epilogue:
	pop $s0
	pop $ra
	li $v0, 0
	jr	$ra


################################################################################
# .TEXT <do_tick>
	.text
do_tick:
	# Subset:   3
	#
	# Args:
	#   - $a0: char map[MAP_HEIGHT][MAP_WIDTH]
	#   - $a1: struct Player *player
	#   - $a2: struct BlockSpawner *block_spawner
	#
	# Returns:  None
	#
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   do_tick
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

do_tick__prologue:
do_tick__body:
do_tick__epilogue:
	jr	$ra

################################################################################
################################################################################
###                   PROVIDED FUNCTIONS — DO NOT CHANGE                     ###
################################################################################
################################################################################

################################################################################
# .TEXT <get_seed>
get_seed:
	# Args:     None
	#
	# Returns:  None
	#
	# Frame:    []
	# Uses:     [$v0, $a0]
	# Clobbers: [$v0, $a0]
	#
	# Locals:
	#   - $v0: seed
	#
	# Structure:
	#   get_seed
	#   -> [prologue]
	#     -> body
	#       -> invalid_seed
	#       -> seed_ok
	#   -> [epilogue]

get_seed__prologue:
get_seed__body:
	li	$v0, 4				# syscall 4: print_string
	la	$a0, get_seed__prompt_msg
	syscall					# printf("Enter a non-zero number for the seed: ")

	li	$v0, 5				# syscall 5: read_int
	syscall					# scanf("%d", &seed);
	sw	$v0, g_rng_state		# g_rng_state = seed;

	bnez	$v0, get_seed__seed_ok		# if (seed == 0) {
get_seed__invalid_seed:
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, get_seed__prompt_invalid_msg
	syscall					#   printf("Invalid seed!\n");

	li	$v0, 10				#   syscall 10: exit
	li	$a0, 1
	syscall					#   exit(1);

get_seed__seed_ok:				# }
	li	$v0, 4				# sycall 4: print_string
	la	$a0, get_seed__set_msg
	syscall					# printf("Seed set to ");

	li	$v0, 1				# syscall 1: print_int
	lw	$a0, g_rng_state
	syscall					# printf("%d", g_rng_state);

	li	$v0, 11				# syscall 11: print_char
	la	$a0, '\n'
	syscall					# putchar('\n');

get_seed__epilogue:
	jr	$ra				# return;


################################################################################
# .TEXT <rng>
rng:
	# Args:     None
	#
	# Returns:  $v0: unsigned
	#
	# Frame:    []
	# Uses:     [$v0, $a0, $t0, $t1, $t2]
	# Clobbers: [$v0, $a0, $t0, $t1, $t2]
	#
	# Locals:
	#   - $t0 = copy of g_rng_state
	#   - $t1 = bit
	#   - $t2 = temporary register for bit operations
	#
	# Structure:
	#   rng
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

rng__prologue:
rng__body:
	lw	$t0, g_rng_state

	srl	$t1, $t0, 31		# g_rng_state >> 31
	srl	$t2, $t0, 30		# g_rng_state >> 30
	xor	$t1, $t2		# bit = (g_rng_state >> 31) ^ (g_rng_state >> 30)

	srl	$t2, $t0, 28		# g_rng_state >> 28
	xor	$t1, $t2		# bit ^= (g_rng_state >> 28)

	srl	$t2, $t0, 0		# g_rng_state >> 0
	xor	$t1, $t2		# bit ^= (g_rng_state >> 0)

	sll	$t1, 31			# bit << 31
	srl	$t0, 1			# g_rng_state >> 1
	or	$t0, $t1		# g_rng_state = (g_rng_state >> 1) | (bit << 31)

	sw	$t0, g_rng_state	# store g_rng_state

	move	$v0, $t0		# return g_rng_state

rng__epilogue:
	jr	$ra


################################################################################
# .TEXT <read_char>
read_char:
	# Args:     None
	#
	# Returns:  $v0: unsigned
	#
	# Frame:    []
	# Uses:     [$v0]
	# Clobbers: [$v0]
	#
	# Locals:   None
	#
	# Structure:
	#   read_char
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

read_char__prologue:
read_char__body:
	li	$v0, 12			# syscall 12: read_char
	syscall				# return getchar();

read_char__epilogue:
	jr	$ra
