    # Read three numbers `start`, `stop`, `step`
    # Print the integers bwtween `start` and `stop` moving in increments of size `step`
    #       
    # Before starting work on this task, make sure you set your tab-width to 8!
    # It is also suggested to indent with tabs only.
    #       
    # YOUR-NAME-HERE, DD/MM/YYYY

    #![tabsize(8)]

main:                                       # int main(void)
    la      $a0,    prompt1                 # printf("Enter the starting number: ");
    li      $v0,    4
    syscall 
    li      $v0,    5                       # scanf("%d", start);
    syscall 
    move    $s0,    $v0                     # s0 as start

    la      $a0,    prompt2                 # printf("Enter the stopping number: ");
    li      $v0,    4
    syscall 
    li      $v0,    5                       # scanf("%d", stop);
    syscall 
    move    $s1,    $v0                     # s1 as stop

    la      $a0,    prompt3                 # printf("Enter the step size: ");
    li      $v0,    4
    syscall 
    li      $v0,    5                       # scanf("%d", step);
    syscall 
    move    $s2,    $v0                     # s2 as step

    # Part 1
    bge     $s1,    $s0,        skip_loop1
    bge     $s1,    $zero,      skip_loop1
    bgez    $s2,    skip_loop1
    # for loop
    move    $t0,    $s0
loop1:
    bgt     $t0,    $s1,        loop1_end
    li      $v0,    1
    move    $a0,    $t0
    syscall 
    add     $t0,    $t0,        $s2         # i += step
    j       loop1
loop1_end:
    # end of for loop
skip_loop1:

    # Part 2
    ble     $s1,    $s0,        skip_loop2
    ble     $s1,    $zero,      skip_loop2
    blez    $s2,    skip_loop2
    # for loop
    move    $t0,    $s0
loop2:
    bgt     $t0,    $s1,        loop2_end
    li      $v0,    1
    move    $a0,    $t0
    syscall 
    add     $t0,    $t0,        $s2         # i += step
    j       loop2
loop2_end:
    # end of for loop
skip_loop2:

end:
    li      $v0,    0
    jr      $ra                             # return 0

.data
prompt1:
    .asciiz"Enter the starting number: "
prompt2:
    .asciiz"Enter the stopping number: "
prompt3:
    .asciiz"Enter the step size: "
