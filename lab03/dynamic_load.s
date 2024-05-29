.data

user_prompt_1:
	.asciiz "Enter mips instructions as integers, -1 to finish:\n"
	.asciiz "Starting executing instructions\n"

user_prompt_2:
	.asciiz "Finished executing instructions\n"

.text

main:
	li $v0, 4
	la $a0, user_prompt_1
	syscall

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

	li $v0, 4
	la $a0, user_prompt_2
	syscall

	jr $ra

command:
	.space 512