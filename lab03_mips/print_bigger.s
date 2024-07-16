# Reads 10 numbers into an array and prints numbers which are
# larger than the final number read.

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  TODO: add your registers here
	#  - $t3: final_number


	# TODO: modify the code below to behave like
	# the provided C program.
scan_loop__init:
	li	$t0, 0				# i = 0;
scan_loop__cond:
	bge	$t0, ARRAY_LEN, scan_loop__end	# while (i < ARRAY_LEN) {

scan_loop__body:
	li	$v0, 5				#   syscall 5: read_int
	syscall					#   
						#
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	sw	$v0, numbers($t1)			#   scanf("%d", &numbers[i]);

	move $t3, $v0 # $t3 = final_number

	addi	$t0, $t0, 1			#   i++;
	j	scan_loop__cond			# }
scan_loop__end:

print_loop__init:
	li	$t0, 0				# i = 0
print_loop__cond:
	bge	$t0, ARRAY_LEN, print_loop__end # while (i < ARRAY_LEN) {

print_loop__body:
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	lw	$a0, numbers($t1)			#   $a0 = numbers[i]

	bge $a0, $t3, then1 			# if (numbers[i] >= final) ...
	j else1
then1:
	li	$v0, 1				#   syscall 1: print_int
	syscall					#   printf("%d", numbers[i]);

	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'			#
	syscall					#   printf("%c", '\n');

else1:
	addi	$t0, $t0, 1			#   i++;
	j	print_loop__cond		# }
print_loop__end:

	li	$v0, 0				
	jr	$ra				# return 0;

	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};
