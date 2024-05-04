    # Calculate 1*1 + 2*2 + ... + 99*99 + 100*100
    # Written by: Abiram Nadarajah <abiramn@cse.unsw.edu.au>
    # Written as a COMP1521 lecture example
    UPPER_BOUND=100
.text
main:
    # Locals:
    # - $t0: int sum
    # - $t1: int i
    # - $t2: temporary value
    li      $t0,                    0                                   # int sum = 0;
loop_i_to_100__init:
    li      $t1,                    1                                   # int i = 0;
loop_i_to_100__cond:
    bgt     $t1,                    UPPER_BOUND,    loop_i_to_100__end  # while (i < UPPER_BOUND) {
loop_i_to_100__body:
    mul     $t2,                    $t1,            $t1                 # sum = (i * i) +
    add     $t0,                    $t0,            $t2                 # sum;
loop_i_to_100__step:
    addi    $t0,                    $t0,            1                   # i++;
    b       loop_i_to_100__cond                                         # }
loop_i_to_100__end:
    li      $v0,                    1                                   # syscall 1: print_int
    move    $a0,                    $t0,            #
    syscall                                                             # printf("%d", sum);
    li      $v0,                    11                                  # syscall 11: print_char
    li      $a0,                    '\n',           #
    syscall                                                             # putchar('\n');
    li      $v0,                    0
    jr      $ra                                                         # return 0;
