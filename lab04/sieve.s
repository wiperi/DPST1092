# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# YOUR-NAME-HERE, DD/MM/YYYY

# Constants
ARRAY_LEN = 1000

main:

	# - $t0: i
	# - $t1: address
	# - $t2: address
	# - $t3: j
	# TODO: add your code here

for1_init:
	li $t0, 2
for1_cond:
	blt $t0, ARRAY_LEN, for1_body
	j for1_end
for1_body:

	# for1 body
	lb $t8, prime($t0)
	beqz $t8, if_non_primei
	# if prime[i]
	li $v0, 1
	move $a0, $t0
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall

for2_init:
	mul $t3, $t0, 2
for2_cond:
	blt $t3, ARRAY_LEN, for2_body
	j for2_end
for2_body:
	li $t8, 0
	sb $t8, prime($t3)
for2_iter:
	add $t3, $t3, $t0
	j for2_cond
for2_end:

if_non_primei:

for1_iter:
	addi $t0, $t0, 1
	j for1_cond
for1_end:

	li	$v0, 0
	jr	$ra			# return 0;

	.data
prime:
	.byte	1:ARRAY_LEN		# uint8_t prime[ARRAY_LEN] = {1, 1, ...};
