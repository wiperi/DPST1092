# Reads a line and prints whether it is a palindrome or not

LINE_LEN = 256

########################################################################
# .TEXT <main>
main:
	# Locals:
	#   - ...

	li	$v0, 4				# syscall 4: print_string
	la	$a0, line_prompt_str		#
	syscall					# printf("Enter a line of input: ");

	li	$v0, 8				# syscall 8: read_string
	la	$a0, line			#
	la	$a1, LINE_LEN			#
	syscall					# fgets(buffer, LINE_LEN, stdin)

	# TODO

while1_init:
	li $t0, 0
while1_cond:
	lb $t1, line($t0)
	bnez $t1, while1_body
	j while1_end
while1_body:
	addi $t0, $t0, 1
	j while1_cond
while1_end:

while2_init:
	li $t8, 0 # $t8 = j
	addi $t7, $t0, -2 # $t7 = k
while2_cond:
	blt $t8, $t7, while2_body
	j while2_end
while2_body:

	lb $t1, line($t8)
	lb $t2, line($t7)
	beq $t1, $t2, if_eq
	# if not eq
	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_not_palindrome_str	#
	syscall					# printf("not palindrome\n");

	j epilogue
if_eq:
	addi $t8, $t8, 1
	addi $t7, $t7, -1

	j while2_cond
while2_end:

	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_palindrome_str	#
	syscall					# printf("palindrome\n");

epilogue:
	li	$v0, 0
	jr	$ra				# return 0;


########################################################################
# .DATA
	.data
# String literals
line_prompt_str:
	.asciiz	"Enter a line of input: "
result_not_palindrome_str:
	.asciiz	"not palindrome\n"
result_palindrome_str:
	.asciiz	"palindrome\n"

# Line of input stored here
line:
	.space	LINE_LEN

