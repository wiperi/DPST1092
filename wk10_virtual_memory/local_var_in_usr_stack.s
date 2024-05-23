.data
    # 数据段
    result: .word 0  # 存储结果的地方

.text
.globl main

main:
    # 调用sum_of_ten函数
    jal sum_of_ten

    # 存储返回值到result
    sw $v0, result

    # 退出程序
    li $v0, 10   # syscall 10是退出程序
    syscall




sum_of_ten:
    addi $sp, $sp, -44   # 为10个int局部变量和保存的ra分配空间，每个4字节，加上ra一共44字节
    sw $ra, 40($sp)      # 保存返回地址

    # 初始化局部变量a1, a2, ..., a10为1
    li $t0, 1
    sw $t0, 0($sp)
    sw $t0, 4($sp)
    sw $t0, 8($sp)
    sw $t0, 12($sp)
    sw $t0, 16($sp)
    sw $t0, 20($sp)
    sw $t0, 24($sp)
    sw $t0, 28($sp)
    sw $t0, 32($sp)
    sw $t0, 36($sp)

    # 计算a1 + a2 + ... + a10
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    lw $t3, 8($sp)
    lw $t4, 12($sp)
    lw $t5, 16($sp)
    lw $t6, 20($sp)
    lw $t7, 24($sp)
    lw $t8, 28($sp)
    lw $t9, 32($sp)
    lw $s0, 36($sp)

    add $t1, $t1, $t2
    add $t1, $t1, $t3
    add $t1, $t1, $t4
    add $t1, $t1, $t5
    add $t1, $t1, $t6
    add $t1, $t1, $t7
    add $t1, $t1, $t8
    add $t1, $t1, $t9
    add $t1, $t1, $s0

    # 返回和
    move $v0, $t1

    # 恢复返回地址并释放栈空间
    lw $ra, 40($sp)
    addi $sp, $sp, 44

    jr $ra
