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
	# Uses:     [...]
	# Clobbers: [...]
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
	blt $t0, MAP_HEIGHT, init_map__for1_iter
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

	# map[6][0] = WALL_CHAR;
	li $t0, 6 			# 6 * row_length * sizeof(char) + map
	mul $t2, $t0, MAP_WIDTH
	mul $t2, $t2, 1
	add $t2, $a0, $t2

	li $t3, WALL_CHAR
	sb $t3, ($t2) 			# map[6][0] = WALL_CHAR;

	# map[6][1] = TRAIN_CHAR;
	li $t0, 6 			# 6 * row_length * sizeof(char)
	mul $t2, $t0, MAP_WIDTH
	mul $t2, $t2, 1
	li $t0, 1			# 1 * sizeof(char)
	mul $t3, $t0, 1
	add $t2, $t2, $t3		# 6 * row_length * sizeof(char) + 1 * sizeof(char)
	add $t2, $a0, $t2		# map + ...

	li $t3, TRAIN_CHAR
	sb $t3, ($t2) 			# map[6][1] = TRAIN_CHAR;

	# map[6][2] = CASH_CHAR;
	li $t0, 6 			# 6 * row_length * sizeof(char)
	mul $t2, $t0, MAP_WIDTH
	mul $t2, $t2, 1
	li $t0, 2			# 2 * sizeof(char)
	mul $t3, $t0, 1
	add $t2, $t2, $t3		# 6 * row_length * sizeof(char) + 2 * sizeof(char)
	add $t2, $a0, $t2		# map + ...

	li $t3, CASH_CHAR
	sb $t3, ($t2) 			# map[6][2] = CASH_CHAR;

	# map[8][2] = BARRIER_CHAR;
	li $t0, 8 			# 8 * row_length * sizeof(char)
	mul $t2, $t0, MAP_WIDTH
	mul $t2, $t2, 1
	li $t0, 2			# 2 * sizeof(char)
	mul $t3, $t0, 1
	add $t2, $t2, $t3		# 8 * row_length * sizeof(char) + 2 * sizeof(char)
	add $t2, $a0, $t2		# map + ...

	li $t3, BARRIER_CHAR
	sb $t3, ($t2) 			# map[8][2] = BARRIER_CHAR;

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
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
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
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   display_game
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

display_game__prologue:
display_game__body:
display_game__epilogue:
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
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   maybe_print_player
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_print_player__prologue:
maybe_print_player__body:
maybe_print_player__epilogue:
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
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   handle_command
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_command__prologue:
handle_command__body:
handle_command__epilogue:
	jr	$ra


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
	# Frame:    [...]
	# Uses:     [...]
	# Clobbers: [...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   handle_collision
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

handle_collision__prologue:
handle_collision__body:
handle_collision__epilogue:
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
	#   - ...
	#
	# Structure:
	#   maybe_pick_new_chunk
	#   -> [prologue]
	#     -> body
	#   -> [epilogue]

maybe_pick_new_chunk__prologue:
maybe_pick_new_chunk__body:
maybe_pick_new_chunk__epilogue:
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
