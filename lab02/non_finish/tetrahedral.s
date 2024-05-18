    # Read a number n and print the first n tetrahedral numbers
    # https://en.wikipedia.org/wiki/Tetrahedral_number
    #       
    # Before starting work on this task, make sure you set your tab-width to 8!
    # It is also suggested to indent with tabs only.
    #       
    # YOUR-NAME-HERE, DD/MM/YYYY

    #![tabsize(8)]
.data
prompt:
    .asciiz"Enter how many: "

.text

# how_many: $t0
# n: $t1
# total: $t2
# j: $t3
# i: $t4
main:

    la      $a0,    prompt      # printf("Enter how many: ");
    li      $v0,    4
    syscall 

    li      $v0,    5           # scanf("%d", number);
    syscall 
	move $t0, $v0

	li $t1, 1 					# n = 1;

while1_con:
	ble $t1, $t0, while1_body 	# while (n <= how_many)
	j while1_end
while1_body:
	li $t2, 0 					# total = 0;
	li $t3, 1 					# j = 1
while2_con:
	ble $t3, $t1, while2_body 	# while (j <= n)
	j while2_end
while2_body:
	li $t4, 1 					# i = 1;
while3_con:
	ble $t4, $t3, while3_body 	# while (i <= j)
	j while3_end
while3_body:
	add $t2, $t2, $t4 			# total = total+ i;
	add $t4, $t4, 1 			# i = i + 1
	j while3_con
while3_end:
	add $t3, $t3, 1 			# j = j + 1
	j while2_con
while2_end:
	li $v0, 1					# printf("%d\n", total);
	move $a0, $t2
	syscall

	li $v0, 11
	la $a0, '\n'
	syscall

	add $t1, $t1, 1 			# n = n + 1

	j while1_con
while1_end:

end:
    li      $v0,    0
    jr      $ra                 # return 0

