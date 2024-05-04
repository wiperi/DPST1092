# simple example of placing return address ($ra) and $a0 on the stack
# recursive function which prints first 20 powers of two in reverse

main:
    begin               # move frame pointer
    push  $ra           # save $ra onto stack

    li    $a0, 1
    jal   two           # two(1);

    pop   $ra           # recover $ra from stack
    end                 # move frame pointer back

    li    $v0, 0        # return 0
    jr    $ra           #


two:
    begin               # move frame pointer
    # save environment
    push  $ra           # save $ra onto stack
    push  $s0           # save $s0 onto stack

    move  $s0, $a0

    bge   $a0, 1000000, two_end_if
    mul   $a0, $a0, 2
    jal   two
two_end_if:

    move  $a0, $s0
    li    $v0, 1        # printf("%d");
    syscall

    li    $a0, '\n'     # printf("%c", '\n');
    li    $v0, 11
    syscall

    # recover environment
    pop   $s0           # recover $s0 from stack
    pop   $ra           # recover $ra from stack
    end                 # move frame pointer back

    jr    $ra           # return from two
