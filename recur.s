.text

main:
	push $ra
	li $a0, 4
	jal sumTo

	pop $ra
	jr $ra
	



sumTo:
	push $ra

	beq $a0, 0, return_0 
	j recur_call
return_0:
	li $v0, 0
	j sumTo_epiloge
recur_call:
	push $a0
	addi $a0, $a0, -1
	jal sumTo
	pop $a0
	
	add $v0, $a0, $v0
	j sumTo_epiloge

sumTo_epiloge:
	pop $ra
	jr $ra