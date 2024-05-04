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

    li $t0, 2 # int i = 2;
loop1_con:
    # if (i < ARRAY_LEN) goto loop1_body;
    # goto loop1_end;
	blt $t0, ARRAY_LEN, loop1_body
	b loop1_end
loop1_body:

    # if (prime[i]) goto if1_then;
    # goto if1_else;
	mul $t1, $t0, 4
	addi $t1, prime
	lw $t1, ($t1)
	bnez $t1, if1_then
	b if1_else

if1_then:
    # printf("%d\n", i);
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 11
	li $a0, '\n'
	syscall

for1_init:
    # int j = 2 * i;
	mul $t3, $t0, 2
for2_con:
    # if (j < ARRAY_LEN) goto for2_body;
    # goto for2_end;
	blt $t3, ARRAY_LEN, for2_body
	b for2_end
for2_body:
    # prime[j] = 0;
	# j += i;
    # goto for2_con;
	mul $t1, $t0, 4
	addi $t1, $t1, prime
	sw $zero, ($t1)

	add $t3, $t3, $t0
	b for2_con
for2_end:

if1_else:
if1_end:

	# i++'
    # goto loop1_con;
	addi $t0, 1
	b loop1_con
loop1_end:

	li	$v0, 0
	jr	$ra			# return 0;

	.data
prime:
	.byte	1:ARRAY_LEN		# uint8_t prime[ARRAY_LEN] = {1, 1, ...};
