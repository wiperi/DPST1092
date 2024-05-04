.data   
prompt1:    .asciiz "Enter first number: "
prompt2:    .asciiz "Enter second number: "
res1:       .asciiz "The sum of all numbers between "
res2:       .asciiz " and "
res3:       .asciiz " (inclusive) is: "
res4:       .asciiz "\n"

.text   

main:       
    li      $v0,    4
    la      $a0,    prompt1
    syscall                                             # print prompt1

    li      $v0,    5
    syscall 
    move    $t0,    $v0                                 # get t0


    li      $v0,    4
    la      $a0,    prompt2
    syscall                                             # print prompt2

    li      $v0,    5
    syscall 
    move    $t1,    $v0                                 # get t1


    sub     $t2,    $t1,        $t0                     # t2 = t1 - t0
    addi    $t2,    $t2,        1                       # t2 = t2 + 1


    add     $t3,    $t0,        $t1                     # t3 = t0 + t1

    # t4 as gaussian_sum
    mul     $t4,    $t2,        $t3                     # t4 = t2 * t3
    div     $t4,    $t4,        2                       # t4 = t4 / 2


    li      $v0,    4
    la      $a0,    res1
    syscall                                             # print res1


    li      $v0,    1
    move    $a0,    $t0                                 # print t0
    syscall 

    li      $v0,    4
    la      $a0,    res2
    syscall                                             # print res2



    li      $v0,    1
    move    $a0,    $t1                                 # print t1
    syscall 

    li      $v0,    4
    la      $a0,    res3
    syscall                                             # print res3



    li      $v0,    1
    move    $a0,    $t4                                 # print t4
    syscall 

    li      $v0,    4
    la      $a0,    res4
    syscall                                             # print res4


    jr      $ra