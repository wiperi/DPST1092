########################################################################
# .DATA
	.data
speak_str:
	.asciiz	"speak"

daffy_str:
	.asciiz	"Daffy"

clifford_str:
	.asciiz	"Clifford"

scruffles_str:
	.asciiz	"Scruffles"

########################################################################
# .TEXT <main>
	.text
main:
main__prologue:
	begin
	push	$ra
	push	$s0
	push	$s1
	push	$s2

main__body:
	la	$a0, daffy_str
	la	$a1, duck_speak
	jal	make_animal
	move	$s0, $v0

	la	$a0, clifford_str
	la	$a1, dog_speak
	jal	make_animal
	move	$s1, $v0

	la	$a0, scruffles_str
	la	$a1, cat_speak
	jal	make_animal
	move	$s2, $v0


	move	$a0, $s0
	la	$a1, speak_str
	jal	obj_call

	move	$a0, $s1
	la	$a1, speak_str
	jal	obj_call

	move	$a0, $s2
	la	$a1, speak_str
	jal	obj_call

main__epilogue:
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end

	li	$v0, 0
	jr	$ra

make_animal:
	begin
	push	$ra
	push	$s0

	move	$s0, $a1

	li	$a1, 1
	jal	make_object

	move	$a0, $v0
	la	$a1, speak_str
	move	$a2, $s0
	jal	obj_define

	pop	$s0
	pop	$ra
	end

	jr	$ra


########################################################################
# .DATA
	.data
duck_str:
	.asciiz	" says quack!\n"

########################################################################
# .TEXT <duck_speak>
	.text
duck_speak:
	li	$v0, 4
	syscall

	li	$v0, 4
	la	$a0, duck_str
	syscall

	jr	$ra

########################################################################
# .DATA
	.data
dog_str:
	.asciiz	" says woof!\n"

########################################################################
# .TEXT <dog_speak>
	.text
dog_speak:
	li	$v0, 4
	syscall

	li	$v0, 4
	la	$a0, dog_str
	syscall

	jr	$ra

########################################################################
# .DATA
	.data
cat_str:
	.asciiz	" says meow!\n"

########################################################################
# .TEXT <cat_speak>
	.text
cat_speak:
	li	$v0, 4
	syscall

	li	$v0, 4
	la	$a0, cat_str
	syscall

	jr	$ra



