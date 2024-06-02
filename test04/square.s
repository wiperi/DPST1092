main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t0, $v0

	# $t0 = x

while_init:
	li $t8, 0
while_cond:
	blt $t8, $t0, while_body
	j while_end
while_body:


while2_init:
	li $t7, 0
while2_cond:
	blt $t7, $t0, while2_body
	j while2_end
while2_body:
	li $v0, 11
	la $a0, '*'
	syscall
	addi $t7, $t7, 1

	j while2_cond
while2_end:
	addi $t8, $t8, 1

	li $v0, 11
	la $a0, '\n'
	syscall

	j while_cond
while_end:


end:
	li	$v0, 0		# return 0
	jr	$ra