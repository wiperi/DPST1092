########################################################################
# .DATA
	.data
number:
	.word	0

add_5_str:
	.asciiz	"add_5"

get_doubled_str:
	.asciiz	"get_doubled"

########################################################################
# .TEXT <main>
	.text
main:
main__prologue:
	begin
	push	$ra
	push	$s0

main__body:
	la	$a0, number
	li	$a1, 2
	jal	make_object
	move	$s0, $v0

	move	$a0, $s0
	la	$a1, add_5_str
	la	$a2, add_5
	jal	obj_define

	move	$a0, $s0
	la	$a1, get_doubled_str
	la	$a2, get_doubled
	jal	obj_define

	move	$a0, $s0
	la	$a1, add_5_str
	jal	obj_call

	move	$a0, $s0
	la	$a1, get_doubled_str
	jal	obj_call

	lw	$a0, ($v0)
	li	$v0, 1
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall

main__epilogue:
	pop	$s0
	pop	$ra
	end

	li	$v0, 0
	jr	$ra



########################################################################
# .TEXT <add_5>
	.text
add_5:
	lw	$t0, ($a0)
	addi	$t0, 5
	sw	$t0, ($a0)

	jr	$ra



########################################################################
# .TEXT <get_doubled>
	.text
get_doubled:
get_doubled__prologue:
	begin
	push	$ra
	push	$s0

get_doubled__body:
	move	$s0, $a0

	li	$a0, SIZEOF_INT
	jal	bumpalo

	lw	$t0, ($s0)
	mul	$t0, 2

	sw	$t0, ($v0)

get_doubled__epilogue:
	pop	$s0
	pop	$ra
	end

	jr	$ra
