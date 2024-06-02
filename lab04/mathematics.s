# YOUR-NAME-HERE, DD/MM/YYYY

########################################################################
# .DATA
# Here are some handy strings for use in your code.

	.data
prompt_str:
	.asciiz "Enter a random seed: "
result_str:
	.asciiz "The random result is: "

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
	begin

	# TODO: add code to set up your stack frame here
	push $ra
	push $s0

main__body:
	# TODO: complete your function body here
	li $v0, 4
	la $a0, prompt_str
	syscall

	li $v0, 5
	syscall

	move $a0, $v0
	jal seed_rand # seed_rand

	li $a0, 100
	jal rand # rand()

	move $s0, $v0 # $s0 = value

	# debug
	li $v0, 1
	move $a0, $s0
	syscall

	move $a0, $s0
	jal add_rand
	move $s0, $v0

	# debug
	li $v0, 1
	move $a0, $s0
	syscall

	move $a0, $s0
	jal sub_rand
	move $s0, $v0

	# debug
	li $v0, 1
	move $a0, $s0
	syscall

	move $a0, $s0
	jal seq_rand
	move $s0, $v0

	# debug
	li $v0, 1
	move $a0, $s0
	syscall

	li $v0, 4
	la $a0, result_str
	syscall

	li $v0, 1
	move $a0, $s0
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall

main__epilogue:
	# TODO: add code to clean up stack frame here
	pop $s0
	pop $ra

	end

	li	$v0, 0
	jr	$ra				# return 0;

########################################################################
# .TEXT <add_rand>
	.text
add_rand:
	# Args:
	#   - $a0: int value
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
	#   - add_rand
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

add_rand__prologue:
	begin

	# TODO: add code to set up your stack frame here
	push $ra
	

add_rand__body:

	# TODO: complete your function body here
	push $a0
	li $a0, 0xffff
	jal rand
	pop $a0

	add $v0, $a0, $v0

add_rand__epilogue:
	
	# TODO: add code to clean up stack frame here
	pop $ra

	end

	jr	$ra


########################################################################
# .TEXT <sub_rand>
	.text
sub_rand:
	# Args:
	#   - $a0: int value
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
	#   - sub_rand
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

sub_rand__prologue:
	begin

	# TODO: add code to set up your stack frame here
	push $ra

sub_rand__body:

	# TODO: complete your function body here
	push $a0
	jal rand
	pop $a0

	sub $v0, $a0, $v0

sub_rand__epilogue:
	
	# TODO: add code to clean up stack frame here
	pop $ra

	end

	jr	$ra

########################################################################
# .TEXT <seq_rand>
	.text
seq_rand:
	# Args:
	#   - $a0: int value
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
	#   - seq_rand
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

seq_rand__prologue:
	begin

	# TODO: add code to set up your stack frame here
	push $ra

seq_rand__body:

	# TODO: complete your function body here
	push $a0
	li $a0, 100
	jal rand
	pop $a0
	move $s0, $v0 # $t0 = limit

for_init:
	li $t8, 0
for_cond:
	blt $t8, $s0, for_body
	j for_end
for_body:
	push $a0
	push $t8
	jal add_rand
	pop $t8
	pop $a0

	move $a0, $v0
for_iter:
	addi $t8, $t8, 1
	j for_cond
for_end:

	move $v0, $a0

seq_rand__epilogue:
	
	# TODO: add code to clean up stack frame here
	pop $ra

	end
	
	jr	$ra



##
## The following are two utility functions, provided for you.
##
## You don't need to modify any of the following,
## but you may find it useful to read through.
## You'll be calling these functions from your code.
##

OFFLINE_SEED = 0x7F10FB5B

########################################################################
# .DATA
	.data
	
# int random_seed;
	.align 2
random_seed:
	.space 4


########################################################################
# .TEXT <seed_rand>
	.text
seed_rand:
# DO NOT CHANGE THIS FUNCTION

	# Args:
	#   - $a0: unsigned int seed
	# Returns: void
	#
	# Frame:	[]
	# Uses:		[$a0, $t0]
	# Clobbers:	[$t0]
	#
	# Locals:
	#   - $t0: offline_seed
	#
	# Structure:
	#   - seed_rand

	li	$t0, OFFLINE_SEED		# const unsigned int offline_seed = OFFLINE_SEED;
	xor	$t0, $a0			# random_seed = seed ^ offline_seed;
	sw	$t0, random_seed

	jr	$ra				# return;

########################################################################
# .TEXT <rand>
	.text
rand:
# DO NOT CHANGE THIS FUNCTION

	# Args:
	#   - $a0: unsigned int n
	# Returns:
	#   - $v0: int
	#
	# Frame:    []
	# Uses:     [$a0, $v0, $t0]
	# Clobbers: [$v0, $t0]
	#
	# Locals:
	#   - $t0: int rand
	#
	# Structure:
	#   - rand

	lw	$t0, random_seed 		# unsigned int rand = random_seed;
	multu	$t0, 0x5bd1e995  		# rand *= 0x5bd1e995;
	mflo	$t0
	addiu	$t0, 12345       		# rand += 12345;
	sw	$t0, random_seed 		# random_seed = rand;

	remu	$v0, $t0, $a0    
	jr	$ra              		# return rand % n;
