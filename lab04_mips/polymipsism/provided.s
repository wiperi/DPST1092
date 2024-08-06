########################################################################
# .TEXT <object_size>
	.text
object_size:
	li	$v0, SIZEOF_VOID_STAR
	addi	$v0, SIZEOF_2_SIZE_T
	li	$t0, SIZEOF_CHAR_STAR
	addi	$t0, SIZEOF_VOID_STAR
	mul	$t0, $a0
	add	$v0, $t0

	jr	$ra


########################################################################
# .TEXT <obj_data>
	.text
obj_data:
	move	$v0, $a0
	jr	$ra


########################################################################
# .TEXT <obj_capacity>
	.text
obj_capacity:
	addi	$v0, $a0, SIZEOF_VOID_STAR
	jr	$ra


########################################################################
# .TEXT <obj_len>
	.text
obj_len:
	addi	$v0, $a0, SIZEOF_VOID_STAR
	addi	$v0, SIZEOF_SIZE_T
	jr	$ra


########################################################################
# .TEXT <obj_nth_fn_name>
	.text
obj_nth_fn_name:
	addi	$v0, $a0, SIZEOF_VOID_STAR
	addi	$v0, SIZEOF_2_SIZE_T

	li	$t0, SIZEOF_CHAR_STAR
	addi	$t0, SIZEOF_VOID_STAR
	mul	$t0, $a1

	add	$v0, $t0
	jr	$ra


########################################################################
# .TEXT <obj_nth_fn_ptr>
	.text
obj_nth_fn_ptr:
	addi	$v0, $a0, SIZEOF_VOID_STAR
	addi	$v0, SIZEOF_2_SIZE_T

	li	$t0, SIZEOF_CHAR_STAR
	addi	$t0, SIZEOF_VOID_STAR
	mul	$t0, $a1

	add	$v0, $t0
	addi	$v0, SIZEOF_CHAR_STAR
	jr	$ra


########################################################################
# .TEXT <streq>
streq:
streq__prologue:
	begin
	push	$ra

streq__body:
	lb	$t0, ($a0)
	bnez	$t0, streq__else_1

	lb	$v0, ($a1)
	not	$v0
	b	streq__epilogue

streq__else_1:
	lb	$t1, ($a1)
	beq	$t0, $t1, streq__else_2

	li	$v0, 0
	b	streq__epilogue

streq__else_2:
	addi	$a0, 1
	addi	$a1, 1
	jal	streq

streq__epilogue:
	pop	$ra
	end

	jr	$ra


########################################################################
# .TEXT <bumpalo>
bumpalo:
	move	$t0, $a0

	li	$v0, 9
	li	$a0, 0
	syscall

	move	$a0, $t0
	move	$t0, $v0
	li	$v0, 9
	syscall

	move	$v0, $t0
	jr	$ra
