# Reads 10 numbers into an array, bubblesorts them
# and then prints the 10 numbers
# YOUR-NAME-HERE, DD/MM/YYYY

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  TODO: add your registers here

scan_loop__init:
	li	$t0, 0				# i = 0
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
	b	scan_loop__cond			# }
scan_loop__end:

	# TODO: add your code here!
swap_loop__init:
	li	$t8, 1				# $t8 = swapped = 1
swap_loop__cond:
	bnez $t8, swap_loop__body
	j swap_loop__end
swap_loop__body:
# swap body begin
inner_loop__init:
	li $t8, 0
	li $t0, 1	# $t0 = i = 1
inner_loop__cond:
	blt $t0, ARRAY_LEN, inner_loop__body
	j inner_loop__end
inner_loop__body:
	mul $t1, $t0, 4
	lw $t2, numbers($t1) # $t2 = numbers[i]
	addi $t1, $t1, -4
	lw $t3, numbers($t1) # $t3 = numbers[i-1]

	bge $t2, $t3, if_x_ge_y
	sw $t2, numbers($t1)
	addi $t1, $t1, 4
	sw $t3, numbers($t1)
if_x_ge_y:
	addi $t0, $t0, 1
	j inner_loop__cond
inner_loop__end:
	j swap_loop__cond
# swap body end
swap_loop__end:



print_loop__init:
	li	$t0, 0				# i = 0
print_loop__cond:
	bge	$t0, ARRAY_LEN, print_loop__end	# while (i < ARRAY_LEN) {

print_loop__body:
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	lw	$a0, ($t2)			#
	li	$v0, 1				#   syscall 1: print_int
	syscall					#   printf("%d", numbers[i]);

	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'			#
	syscall					#   printf("%c", '\n');

	addi	$t0, $t0, 1			#   i++
	b	print_loop__cond		# }
print_loop__end:
	
	li	$v0, 0
	jr	$ra				# return 0;


	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};
