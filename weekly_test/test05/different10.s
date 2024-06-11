# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#   - $t0: int x
	#   - $t2: int n_seen
	#   - $t3: temporary result
	#   - $t4: temporary result

slow_loop__init:
	li	$t2, 0				# n_seen = 0;
slow_loop__cond:
	bge	$t2, ARRAY_LEN, slow_loop__end	# while (n_seen < ARRAY_LEN) {

slow_loop__body:
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, prompt_str			#
	syscall					#   printf("Enter a number: ");

	li	$v0, 5				#   syscall 5: read_int
	syscall					#
	move	$t0, $v0			#   scanf("%d", &x);

	# Your code goes here

while__init:
	li $t8, 0 # $t8 = int i
while__cond:
	blt $t8, $t2, while__body
	j while__end
while__body:
	mul $t3, $t8, 4
	lw $t3, numbers($t3)

	bne $t0, $t3, if_x_neq_numbersi
	# x == numbers[i]
	j while__end
if_x_neq_numbersi:
	addi $t8, $t8, 1
	j while__cond
while__end:

	bne $t8, $t2, i_neq_n_seem
	# i == n_seen
	mul	$t3, $t2, 4			#
	sw	$t0, numbers($t3)		#   numbers[n_seen] = x;

	addi	$t2, $t2, 1			#   n_seen++;
i_neq_n_seem:
	j	slow_loop__cond
slow_loop__end:					# }

	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_str			#
	syscall					# printf("10th different number was: ");

	li	$v0, 1				# syscall 1: print_int
	move	$a0, $t0			#
	syscall					# printf("%d", x);

	li	$v0, 11				# syscall 11: print_char	
	li	$a0, '\n'			#
	syscall					# putchar('\n');

	li	$v0, 0
	jr	$ra				# return 0;

########################################################################
# .DATA
	.data
numbers:
	.space 4 * ARRAY_LEN			# int numbers[ARRAY_LEN];
prompt_str:
	.asciiz	"Enter a number: "
result_str:
	.asciiz	"10th different number was: "
