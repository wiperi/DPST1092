main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t0, $v0

	li	$v0, 5		# scanf("%d", &y);
	syscall			#
	move	$t1, $v0

	# $t0 = x
	# $t1 = y
	# $t8 = i

while_init:
	addi $t8, $t0, 1
while_cond:
	blt $t8, $t1, while_body
	j while_end
while_body:

	beq $t8, 13, if_i_eq_13
	# if != 13
	move	$a0, $t8		# printf("%d\n", 42);
	li	$v0, 1
	syscall	

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall	
if_i_eq_13:

	addi $t8, $t8, 1
	
	j while_cond
while_end:



end:
	li	$v0, 0         # return 0
	jr	$ra



