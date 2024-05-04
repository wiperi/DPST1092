# Reads 10 numbers into an array
# printing 0 if they are in non-decreasing order
# or 1 otherwise.
# YOUR-NAME-HERE, DD/MM/YYYY

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  TODO: add your registers here
	#  - $t3: swapped
scan_loop__init:
	li	$t0, 0				# i = 0;
scan_loop__cond:
	bge	$t0, ARRAY_LEN, scan_loop__end	# while (i < ARRAY_LEN) {

scan_loop__body:
	li	$v0, 5				#   syscall 5: read_int
	syscall					#   
						#
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	sw	$v0, ($t2)			#   scanf("%d", &numbers[i]);

	addi	$t0, $t0, 1			#   i++;
	j	scan_loop__cond			# }
scan_loop__end:

	# TODO: add your code here!
loop1_init:
	li $t3, 0 # $t3 = swapped = 0
	li $t0, 1 # $t0 = i = 1
loop1_con:
	bge $t0, ARRAY_LEN, loop1_end # while (i < ARRAY_LEN)
loop1_body:
	li $t4, 4
	mul $t1, $t0, $t4 	      # i * 4
	addi $t1, $t1, numbers # numbers + i * 4
	lw $t1, ($t1) # x = numbers[i]

	mul $t2, $t0, $t4 	      # i * 4
	addi $t2, $t2, numbers # numbers + i * 4
	sub $t2, $t2, 4 # numbers[i - 1]
	lw $t2, ($t2) # y = numbers[i - 1]

if1_con:
	blt $t1, $t2, then1
	j if1_end
then1:
	li $t3, 1
if1_end:

	addi $t0, $t0, 1 # i++
	j loop1_con
loop1_end:

	li	$v0, 1				# syscall 1: print_int
	move  $a0, $t3 			#
	syscall					# printf("%d", 42)

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'			#
	syscall					# printf("%c", '\n');

	li	$v0, 0
	jr	$ra				# return 0;

	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};
