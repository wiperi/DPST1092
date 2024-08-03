# DPST1092 23T1 ... supp, question 3
# The provided code reads an integer and
# prints out the number 42 on a newline.
# Modify this program such that its output
# matches that of supp_q3.c

main:

while_init:
	li $s0, 0 # s0 = value
	li $s1, 0 # s1 = sum
while_cond:
	li $t0, -1
	bne $s0, $t0, while_body
	j while_end
while_body:
	add $s1, $s1, $s0

	li $v0, 5
	syscall
	move $s0, $v0

	j while_cond
while_end:

	li	$v0, 1		# syscall 1: print_int
	move $a0, $s1
	syscall			# printf("%d", sum);

	li	$v0, 11		# syscall 11: print_char
	li	$a0, '\n'	#
	syscall			# putchar('\n');

	li	$v0, 0
	jr	$ra		# return 0;
