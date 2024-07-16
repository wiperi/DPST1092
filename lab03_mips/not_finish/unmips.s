.text
main:
    li      $t0,        data_segment,   +,          1
    addi    $t1,        $t0,            73
    li      $v0,        8
    move    $a0,        $t0
    li      $a1,        72
    syscall 
    li      $v0,        5
    syscall 
    move    $t2,        $v0
    li      $v0,        5
    syscall 
    move    $t3,        $v0
    li      $t4,        0
label_1:
    bge     $t4,        $t2,            label_6
    li      $t5,        0
label_2:
    bge     $t5,        70,             label_5
    add     $t9,        $t0,            $t5
    lb      $t6,        -1($t9)
    lb      $t7,        ($t9)
    lb      $t8,        1($t9)
    sgt     $t6,        $t6,            48
    sgt     $t7,        $t7,            48
    sgt     $t8,        $t8,            48
    mul     $t6,        $t6,            4
    mul     $t7,        $t7,            2
    add     $t8,        $t8,            $t7
    add     $t8,        $t8,            $t6
    move    $t6,        $t3
label_3:
    ble     $t8,        0,              label_4
    div     $t6,        $t6,            2
    addi    $t8,        $t8,            -1
    b       label_3
label_4:
    rem     $t6,        $t6,            2
    addi    $t6,        $t6,            1
    mul     $t6,        $t6,            32
    add     $t9,        $t1,            $t5
    sb      $t6,        ($t9)
    li      $v0,        11
    move    $a0,        $t6
    syscall 
    addi    $t5,        $t5,            1
    b       label_2
label_5:
    li      $a0,        10
    syscall 
    move    $t6,        $t0
    move    $t0,        $t1
    move    $t1,        $t6
    addi    $t4,        1
    b       label_1
label_6:
    li      $v0,        0
    jr      $ra

.data
data_segment:
    .byte0:145