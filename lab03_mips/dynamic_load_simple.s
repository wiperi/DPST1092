.text

main:
	li $t0, 872677418
	sw $t0, command
	li $t0, 65011720
	sw $t0, command + 4
	
	push $ra
	jal command
	pop $ra


	li $v0, 1
	syscall

	jr $ra


command:
	.space 8
	

	