#  print the minimum of two integers
main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			# $t0 = x
	move	$t0, $v0

	li	$v0, 5		# scanf("%d", &y);
	syscall			# $t1 = y
	move	$t1, $v0

	blt $t0, $t1, x_lt_y
	j x_gt_y
x_lt_y:
	li $v0, 1
	move $a0, $t0 # print x
	syscall
	j if_end
x_gt_y:
	li $v0, 1
	move $a0, $t1 # print y
	syscall
if_end:

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

end:
	li	$v0, 0		# return 0
	jr	$ra
