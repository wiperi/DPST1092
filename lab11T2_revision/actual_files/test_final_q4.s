# Call the `final_q4()' function from the command-line.
# See the exam paper and `final_q4.s' file for a description of the question.

# Do not change this file.

# read 10 numbers into an array

.data

# int numbers[10] = {0};
numbers: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

.text
.globl main

main:
    addiu $sp, $sp, -4
    sw    $ra, 0($sp)

    # i = 0
    li    $t0, 0

    # while (i < 10) {
main__read_loop_start:
    bge   $t0, 10, main__read_loop_end

    # scanf("%d", &numbers[i]);
    li    $v0, 5 # read integer from stdin
    syscall      #

    mul   $t1, $t0, 4   # calculate &numbers[i]
    la    $t2, numbers  #
    add   $t3, $t1, $t2 #

    sw    $v0, ($t3) # store entered number in array

    # i++;
    add   $t0, $t0, 1

    # }
    b     main__read_loop_start
main__read_loop_end:

    # answer = final_q4(numbers, 10);
    la    $a0, numbers
    li    $a1, 10
    jal   final_q4
    move  $t0, $v0

    # printf("%d\n", answer);
    li    $v0, 1
    move  $a0, $t0
    syscall
    li    $v0, 11
    li    $a0, '\n'
    syscall

    lw    $ra, 0($sp)
    addiu $sp, $sp, 4

    # return 0
    li    $v0, 0
    jr    $ra
