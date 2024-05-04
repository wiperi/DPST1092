    # read a number n and print the integers 1..n one per line
    #       
    # Before starting work on this task, make sure you set your tab-width to 8!
    # It is also suggested to indent with tabs only.
    #       
    # YOUR-NAME-HERE, DD/MM/YYYY

    #![tabsize(8)]
.text

main:                           # int main(void)
    la      $a0,    prompt      # printf("Enter a number: ");
    li      $v0,    4
    syscall 

    li      $v0,    5           # scanf("%d", number);
    syscall 

    move    $s0,    $v0         # s0 = number
    li      $t0,    1           # t0 as i = 1

loop:
    bgt     $t0,    $s0,    end # if (i > number) goto end

    move    $a0,    $t0         # printf("%d", i);
    li      $v0,    1
    syscall 

    li      $a0,    '\n'        # printf("%c", '\n');
    li      $v0,    11
    syscall 

    addi    $t0,    $t0,    1   # i++

    j       loop

end:
    li      $v0,    0
    jr      $ra                 # return 0

.data
prompt:
    .asciiz"Enter a number: "
