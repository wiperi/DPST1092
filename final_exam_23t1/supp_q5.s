# DPST1092 23T1 ... supp exam, question 5

# Modify the program below such that its output
# matches that of supp_q4

main:
	# li	$v0, 5				# syscall 5: read_int
	# syscall					#
	# move	$t0, $v0			# scanf("%d, &x);

	# # ADD YOUR CODE HERE


	# li	$v0, 1				# syscall 1: print_int
	# li	$a0, 42				#
	# syscall					# printf("%d", 42);

	# li	$v0, 11				# syscall 11: print_char
	# li	$a0, '\n'			#
	# syscall					# putchar('\n');

	li $v0, 5
	syscall
	move $s0, $v0 # s0 = x

	li $s1, 0 # is_window
	li $s2, 0 # win_len
	li $s3, 0 # max_len

for_init:
	li $t8, 0 # t8 = i
for_cond:
	li $t0, 32
	blt $t8, $t0, for_body
	j for_end
for_body:
	srlv $t0, $s0, $t8
	andi $t0, $t0, 1 # t0 = bit

	beq $t0, 1, if_bit_1
	j if_bit_0
if_bit_1:
	#################
	bnez $s1, if_not_window
	li $s1, 1
if_not_window:

	beqz $s1, if_window
	addi $s2, $s2, 1 
if_window:
	##################
	j if_bit_end
if_bit_0:
	##################
	beqz $s1, if_challenge
	# challenge
	ble $s2, $s3, if_update_max
	move $s3, $s2
if_update_max:

	li $s2, 0
if_challenge:
	#////////////////#
	j if_bit_end
if_bit_end:
	addi $t8, $t8, 1
	j for_cond
for_end:

	beqz $s1, if_challenge_tail
	# challenge
	ble $s2, $s3, if_update_max_tail
	move $s3, $s2
if_update_max_tail:
	li $s2, 0
if_challenge_tail:

	# print s3

	li	$v0, 1				# syscall 1: print_int
	move $a0, $s3
	syscall					# printf("%d", 42);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'			#
	syscall					# putchar('\n');

	li	$v0, 0				#
	jr	$ra				# return 0;
