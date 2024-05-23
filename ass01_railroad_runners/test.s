
# Constants
EMPTY_CHAR =		' '
WALL_CHAR =		'w'
TRAIN_CHAR =		't'
CASH_CHAR =		'c'
BARRIER_CHAR =		'b'

MAP_HEIGHT = 		 20
MAP_WIDTH = 		5

.data



g_map: # char[MAP_HEIGHT][MAP_WIDTH]
	.space MAP_HEIGHT * MAP_WIDTH

.text

main:

	push $ra

	la $a0, g_map
	jal init_map

	pop $ra

for1_init:
	li $t0, 0 				# for(int i = 0; ...)
for1_condition:
	blt $t0, MAP_HEIGHT, for1_body
	j for1_end
for1_body:

for2_init:
	li $t1, 0 				# for(int j = 0; ...)
for2_condition:
	blt $t1, MAP_WIDTH, for2_body
	j for2_end
for2_body:
	mul $t2, $t0, MAP_WIDTH 		# i * row_length
	mul $t2, $t2, 1				# i * row_length * sizeof(char)
	mul $t3, $t1, 1 			# j * sizeof(char)
	add $t2, $t2, $t3 			# i * row_length * sizeof(char) + j * sizeof(char)
	add $t2, g_map, $t2 			# map + ...

	lb $t4, ($t2) 			# Load byte from memory at address $t2 into $t4
	li $v0, 11 				# System call code for printing a character
	move $a0, $t4 			# Move the value in $t4 to $a0 (argument register)
	syscall 				# Perform the system call
	
for2_iter:
	add $t1, $t1, 1
	j for2_condition
for2_end:

	li $v0, 11 				# System call code for printing a newline
	li $a0, '\n' 			# ASCII code for newline
	syscall 				# Perform the system call

for1_iter:
	add $t0, $t0, 1
	j for1_condition
for1_end:



	jr $ra


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