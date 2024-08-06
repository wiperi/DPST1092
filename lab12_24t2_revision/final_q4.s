    # return the number of peaks in an array of integers
    #       
    # A peak is a value that is both preceded and succeeded
    # by a value smaller than itself
    #       
    # ie:
    # Both the value before and the value after the current value
    # are smaller than the current value
    #       
    # eg:
    # [1, 3, 2, 5, 4, 4, 9, 0, 1, -9, -5, -7]
    #     ^     ^        ^     ^       ^
    # The value 3, 5, 9, 1, -5 are all peaks in this array
    # So your function should return 5

.text
    .globlfinal_q4

final_q4:
    # YOU DO NOT NEED TO CHANGE THE LINES ABOVE HERE


final_q4_prologue:
    push    $s0
    push    $s1
    push    $ra

    move    $s0,                $a0                         # array
    move    $s1,                $a1                         # length
final_q4_body:

while_init:
    li      $t8,                0                           # int total
    li      $t7,                1                           # int i
while_cond:
    addi    $t0,                $s1,        -1
    blt     $t7,                $t0,        while_body
    j       while_end
while_body:

    mul     $t0,                $t7,        4
    add     $t0,                $t0,        $s0

    lw      $t1,                ($t0)
    lw      $t2,                -4($t0)
    lw      $t3,                4($t0)

    ble     $t1,                $t2,        no_increment
    ble     $t1,                $t3,        no_increment
    j       total_increment
total_increment:
    addi    $t8,                $t8,        1               # total++
no_increment:
    addi    $t7,                $t7,        1
    j       while_cond
while_end:

    move    $v0,                $t8

final_q4_epilogue:
    pop     $ra
    pop     $s1
    pop     $s0
    jr      $ra


    # ADD ANY EXTRA FUNCTIONS BELOW THIS LINE
