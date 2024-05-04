# print array of ints
# i in $t0

main:
    li   $t0, 0          # int i = 0;
loop:
    bge  $t0, 5, end     # if (i >= 5) goto end;

    # int j = numbers[i], j in t3
    la   $t1, numbers    # t1 = numbers;
    mul  $t2, $t0, 4     # t2 = sizeof(int) * i
    add  $t3, $t2, $t1   # t3 = numbers + (sizeof(int) * i)
    
    lw   $a0, 0($t3)     # printf("%d", j);
    li   $v0, 1
    syscall
    li   $a0, '\n'       #   printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t0, $t0, 1     #   i++
    b    loop            # goto loop
end:

    li   $v0, 0          # return 0
    jr   $ra

.data

numbers:                 # int numbers[10] = { 3, 9, 27, 81, 243};
     .word 3, 9, 27, 81, 243
