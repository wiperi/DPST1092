.data

res:
	.byte -1:5

tar:
	.ascii "UNIX"



.text

main:
	# scanf 2 integers
	li $v0, 1
	syscall
	move $s1, $v0

	li $v0, 1
	syscall
	move $s2, $v0

	# m in $s1, n in $s2

	


