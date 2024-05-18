.data
prompt1:
    .asciiz"Enter the starting number: "
prompt2:
    .asciiz"Enter the stopping number: "
prompt3:
    .asciiz"Enter the step size: "

.text

    # start: $t0
    # stop: $t1
    # step: $t2
    # i: $t3
main:

    li      $v0,                    4                                   # printf("Enter the starting number: ");
    la      $a0,                    prompt1
    syscall 

    li      $v0,                    5                                   # scanf("%d", &start);
    syscall 
    move    $t0,                    $v0

    li      $v0,                    4                                   # printf("Enter the stopping number: ");
    la      $a0,                    prompt2
    syscall 

    li      $v0,                    5                                   # scanf("%d", &stop);
    syscall 
    move    $t1,                    $v0

    li      $v0,                    4                                   # printf("Enter the step size: ");
    la      $a0,                    prompt3
    syscall 

    li      $v0,                    5                                   # scanf("%d", &step);
    syscall 
    move    $t2,                    $v0

    blt     $t1,                    $t0,        if_stop_lt_start        #    if (stop < start) {
    j       if_stop_lt_start_end

if_stop_lt_start:
    bge     $t2,                    $zero,      if_stop_lt_start_end    #   if (step < 0)

for1_init:                                                              # for (int i = start; i >= stop; i += step) {
    #     printf("%d\n", i);
    # }

    move    $t3,                    $t0
for1_condition:
    bgt     $t3,                    $t1,        for1_body
    j       for1_end
for1_body:
    li      $v0,                    1
    move    $a0,                    $t3
    syscall 

    li      $v0,                    11
    la      $a0,                    '\n'
    syscall 
for1_iter:
    add     $t3,                    $t3,        $t2
    j       for1_condition
for1_end:

if_stop_lt_start_end:



    bgt     $t1,                    $t0,        if_stop_gt_start        # if (stop > start) {
    j       if_stop_gt_start_end                                        # if (step > 0)

if_stop_gt_start:
    ble     $t2,                    $zero,      if_stop_gt_start_end

for2_init:                                                              # for (int i = start; i <= stop; i += step) {
    #     printf("%d\n", i);
    # }

    move    $t3,                    $t0
for2_condition:
    blt     $t3,                    $t1,        for2_body
    j       for2_end
for2_body:
    li      $v0,                    1
    move    $a0,                    $t3
    syscall 

    li      $v0,                    11
    la      $a0,                    '\n'
    syscall 
for2_iter:
    add     $t3,                    $t3,        $t2
    j       for2_condition
for2_end:

if_stop_gt_start_end:



    jr      $ra                                                         # return 0

