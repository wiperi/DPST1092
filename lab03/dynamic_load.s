.text

main:
while_init:
	li $t8, 0  # $t8 = i = 0
while_cond:
while_body:
	li $v0, 5
	syscall # input in $v0

	beq $v0, -1, while_end

	mul $t0, $t8, 4
	sw $v0, command($t0)

	addi $t8, $t8, 1

	j while_cond
while_end:

	push $ra
	jal command
	pop $ra

	jr $ra

command:
	.space 512