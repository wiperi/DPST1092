########################################################################
# .DATA
# Here are some handy strings for use in your code.
	.data
prompt_m_str:	.asciiz	"Enter m: "
prompt_n_str:	.asciiz	"Enter n: "
result_str_1:	.asciiz	"Ackermann("
result_str_2:	.asciiz	", "
result_str_3:	.asciiz	") = "

########################################################################
# .TEXT <main>
	.text
main:

	# Args: void
	# Returns: int
	#
	# Frame:	[...]
	# Uses: 	[...]
	# Clobbers:	[...]
	#
	# Locals:
	#   - ...
	#
	# Structure:
	#   - main
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

main__prologue:

	# TODO: set up your stack frame
	push $ra
	push $s0
	push $s1

main__body:

	# TODO: add your function body here
	li $v0, 4
	la $a0, prompt_m_str
	syscall

	li $v0, 5
	syscall
	move $s0, $v0 # $s0 = m

	li $v0, 4
	la $a0, prompt_n_str
	syscall

	li $v0, 5
	syscall
	move $s1, $v0 # $s1 = n

	move $a0, $s0
	move $a1, $s1
	jal ackermann # ackermann(m, n)

	move $t0, $v0 # $t0 = f

	li $v0, 4
	la $a0, result_str_1
	syscall

	li $v0, 1
	move $a0, $s0
	syscall

	li $v0, 4
	la $a0, result_str_2
	syscall

	li $v0, 1
	move $a0, $s1
	syscall

	li $v0, 4
	la $a0, result_str_3
	syscall

	li $v0, 1
	move $a0, $t0
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall

main__epilogue:

	# TODO: clean up your stack frame
	pop $s1
	pop $s0
	pop $ra

	li	$v0, 0
	jr	$ra			# return 0;

########################################################################
# .TEXT <ackermann>
	.text
ackermann:

	# Args:
	#   - $a0: int m
	#   - $a1: int n
	# Returns: int
	#
	# Frame:	[]
	# Uses: 	[]
	# Clobbers:	[]
	#
	# Locals:
	#   - .
	#
	# Structure:
	#   - ackermann
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

ackermann__prologue:

	# TODO: set up your stack frame
	push $ra
	push $s0
	push $s1

ackermann__body:

	# TODO: add your function body here
	move $s0, $a0 # $s0 = m
	move $s1, $a1 # $s1 = n

	bne $s0, $zero, ackermann_m_not_zero
	# m == 0
	addi $v0, $s1, 1
	j ackermann__epilogue # return n + 1
ackermann_m_not_zero:

	bne $s1, $zero, ackermann_n_not_zero
	# n == 0
	addi $a0, $s0, -1
	li $a1, 1
	jal ackermann # ackermann(m - 1, n)

	j ackermann__epilogue
ackermann_n_not_zero:

	move $a0, $s0
	addi $a1, $s1, -1
	jal ackermann
	move $a1, $v0

	addi $a0, $s0, -1
	jal ackermann

	j ackermann__epilogue

ackermann__epilogue:

	# TODO: clean up your stack frame
	pop $s1
	pop $s0
	pop $ra

	jr	$ra
