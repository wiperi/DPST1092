.data

res:
	.word 0

tar:
	.ascii "UNIX"

m:
	.word 0
n:
	.word 0



.text
# debug log: misuse lw; can not use lb load value in reg; mistype $t7 to $7; forget to add '\n' at last
main:
	# scanf 2 integers

	li $v0, 5
	syscall
	sw $v0, m

	li $v0, 5
	syscall
	sw $v0, n

while_init:
	li $t8, 0 			# $t8 = target_index
	li $t7, 0 			# $t7 = i
while_cond:
while_body:

	bge $t8, 4, break
	bge $t7, 4, break
	j no_break 
break:
	li $v0, 1
	lw $a0, res
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall

	jr $ra
no_break:

while2_init:
	li $t7, 0
while2_cond:
	lb $t0, m($t7)
	lb $t1, tar($t8)

	bne $t0, $t1, while2_body
	j while2_end
while2_body:
	addi $t7, $t7, 1 		# i++
	j while2_cond
while2_end:

	lb $t0, n($t7)
	sb $t0, res($t8)

	addi $t8, $t8, 1

	j while_cond
while_end:

	


