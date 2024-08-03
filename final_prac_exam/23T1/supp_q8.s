# DPST1092 23T1 ... supp exam, question 8

# The provided code reads a line of input from the user,
# and then prints out "Is substring\n" on a new line.
# Modify it so that it evaluates the inputted boolean
# expression such that it matches supp_q8.c 

#################################################################################
# .DATA
# DO NOT MODIFY THE DATA SEGMENT
	.data
text:
	.space	256
pattern:
	.space  256


# Useful strings
msg_result_false:
	.asciiz	"Is NOT substring\n"
msg_result_true:
	.asciiz	"Is substring\n"
#################################################################################
# .TEXT <main>
	.text
main:
	#ADD/MODIFY CODE TO COMPLETE THIS FUNCTION
main_prologue:
	push $ra
main_body:
	li	$v0, 8			# syscall 8: read_string
	la	$a0, text		#
	la	$a1, 256		#
	syscall				# fgets(text, 256, stdin)

	li $v0, 8
	la $a0, pattern
	la $a1, 256
	syscall				# fgets(pattern, 256, stdin)

	li $a0, text
	li $a1, pattern
	jal is_substring
	bnez $v0, if_is_substring
	j if_is_not_substring
if_is_substring:
	li	$v0, 4			# syscall 4: print_string
	la	$a0, msg_result_true	#
	syscall				# printf("%s", "Is substring\n");
	j if_end
if_is_not_substring:
	li	$v0, 4			# syscall 4: print_string
	la	$a0, msg_result_false	#
	syscall				# printf("%s", "Is substring\n");
	j if_end
if_end:


main_epilogue:
	pop $ra

	li	$v0, 0			#
	jr	$ra			# return 0;


#################################################################################
# .TEXT <is_substring>
is_substring:
is_substring_prologue:
	push $ra
	push $s0
	push $s1

	move $s0, $a0 # str*
	move $s1, $a1 # substr*
is_substring_body:
	lb $t0, ($s0)
	lb $t1, ($s1)
	bne $t0, $t1, if_str_eq_substr
		move $a0, $s0
		move $a1, $s1
		jal match
		beqz $v0, if_match
		li $v0, 1
		j is_substring_epilogue
if_match:
if_str_eq_substr:

	lb $t0, ($s0)
	li $t1, 10
	beq $t0, $t1, if_str_eq_lf
	j else_str_eq_lf 
if_str_eq_lf:
	li $v0, 0
	j is_substring_epilogue
	j if_str_eq_lf_end
else_str_eq_lf:
	addi $a0, $s0, 1
	move $a1, $s1
	jal is_substring
	j is_substring_epilogue
	j if_str_eq_lf_end
if_str_eq_lf_end:

is_substring_epilogue:
	pop $s1
	pop $s0
	pop $ra
	# COMPLETE THIS FUNCTION
	jr	$ra

#################################################################################
# .TEXT <match>
match:
match_prologue:
	push $ra
	push $s0
	push $s1

	move $s0, $a0 # str*
	move $s1, $a1 # substr*
match_body:
	lb $t0, ($s1)
	bne $t0, '\n', if_substr_neq_n 
	li $v0, 1
	j match_epilogue
if_substr_neq_n:

	lb $t0, ($s0)
	bne $t0, '\n', if_str_eq_n
		lb $t0, ($s1)
		beq $t0, '\n', if_substr_neq_crlf
		li $v0, 0
		j match_epilogue
		if_substr_neq_crlf:
if_str_eq_n:

	lb $t0, ($s0)
	lb $t1, ($s1)
	bne $t0, $t1, return_match
	addi $a0, $s0, 1
	addi $a1, $s1, 1
	jal match
	j match_epilogue
return_match:

	li $v0, 0

match_epilogue:
	pop $s1
	pop $s0
	pop $ra
	# COMPLETE THIS FUNCTION
	jr	$ra


