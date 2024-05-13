.data
numbers:
    .word 3, 9, 27, 81, 243, 4, 16, 64, 256, 1024, 5, 25, 125, 625, 3125


.text

main:
    li      $t0,    0                   # int t0 = 0;
loop1:
    bge     $t0,    3,      loop1_end   # if (t0 >= 3) goto loop1_end;

    # // loop1 body
    li      $t1,    0                   # int t1 = 0;
loop2:
    bge     $t1,    5,      loop2_end   # if (t1 >= 5) goto loop2_end;

    # // loop2 body
    li      $t2,    20			# 20 = sizeof(int) * row_length
    mul     $t2,    $t2,    $t0         # int t2 = t0 * row_size

    li      $t3,    4
    mul     $t3,    $t3,    $t1         # int t3 = t1 * col_size

    add     $t2,    $t2,    numbers     # t2 = numbers + t0 * row_size
    add     $t2,    $t2,    $t3         # t2 = numbers + t0 * row_size + t1 * col_size
    lw      $a0,    0($t2)
    li      $v0,    1
    syscall                             # printf("%d", numbers[t0][t1]);

    la      $a0,    ' '
    li      $v0,    11
    syscall                             # printf("%c", ' ');

    addi    $t1,    $t1,    1           # t1++;
    j       loop2                       # goto loop2;
loop2_end:

    li      $a0,    '\n'
    li      $v0,    11
    syscall                             # printf("%c", '\n');

    addi    $t0,    $t0,    1           # t0++;
    j       loop1                       # goto loop1;
loop1_end:

    li      $v0,    0                   # return 0
    jr      $ra