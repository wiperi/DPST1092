# DPST1092 23T1 ... supp exam, question 1

# The provided code reads one integer and prints it.
# Modify it so that it reads two integers (x and y) 
# and prints out the result of the following calculation 
# 1 + x % y

main:
	li	$v0, 5		# syscall 5: read_int
	syscall			#
	move	$s0, $v0	# scanf("%d", &x);
	
	li	$v0, 5		# syscall 5: read_int
	syscall			#
	move	$s1, $v0	# scanf("%d", &x);

	# s0 = x
	# s1 = y

	mod $t0, $s0, $s1
	addi $t0, $t0, 1

	li	$v0, 1		# syscall 1: print_int
	move	$a0, $t0	#
	syscall			# printf("%d", x);
	
	li	$v0, 11		# syscall 11: print_char
	li	$a0, '\n'	#
	syscall			# printf("\n");

	li	$v0, 0
	jr	$ra		# return 0;
