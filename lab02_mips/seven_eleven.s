    # Read a number and print positive multiples of 7 or 11 < n
    #       
    # Before starting work on this task, make sure you set your tab-width to 8!
    # It is also suggested to indent with tabs only.
    #       
    # YOUR-NAME-HERE, DD/MM/YYYY

    #![tabsize(8)]
.text
main:                               # int main(void) {

    la      $a0,        prompt      # printf("Enter a number: ");
    li      $v0,        4
    syscall 

    li      $v0,        5           # scanf("%d", number);
    syscall 
    move    $s0,        $v0         # s0 = number

    li      $s1,        1           # s1 as i = 1

loop:
    bge     $s1,        $s0,    end # if (i >= number) goto end;

    rem     $t0,        $s1,    7   # i % 7
    beqz    $t0,        print       # if (i % 7 == 0) goto print;

    rem     $t0,        $s1,    11  # i % 11
    beqz    $t0,        print       # if (i % 11 == 0) goto print;
    j       no_print

print:
    move    $a0,        $s1         # printf("%d", i);
    li      $v0,        1
    syscall 

    li      $a0,        '\n'        # printf("%c", '\n');
    li      $v0,        11
    syscall 

no_print:
    addi    $s1,        $s1,    1   # i++
    j       loop                    # goto loop

end:
    li      $v0,        0
    jr      $ra                     # return 0

.data
prompt:
    .asciiz"Enter a number: "
