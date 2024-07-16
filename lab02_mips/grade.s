    # read a mark and print the corresponding UNSW grade
    #       
    # Before starting work on this task, make sure you set your tab-width to 8!
    # It is also suggested to indent with tabs only.
    #       
    # YOUR-NAME-HERE, DD/MM/YYYY

    #![tabsize(8)]
.text

main:
    la      $a0,        prompt              # printf("Enter a mark: ");
    li      $v0,        4
    syscall 

    li      $v0,        5                   # scanf("%d", mark);
    syscall 
    move    $s0,        $v0                 # s0 = mark

    blt     $s0,        50,     print_fl    # if (mark < 50) goto f1;

    blt     $s0,        65,     print_ps    # if (mark < 65) goto ps;

    blt     $s0,        75,     print_cr    # if (mark < 75) goto cr;

    blt     $s0,        85,     print_dn    # if (mark < 85) goto dn;

    j    print_hd                        # goto hd;

print_fl:
    la      $a0,        fl                  # printf("FL\n");
    li      $v0,        4
    syscall 
    j       end

print_ps:
    la      $a0,        ps                  # printf("PS\n");
    li      $v0,        4
    syscall 
    j       end

print_cr:
    la      $a0,        cr                  # printf("CR\n");
    li      $v0,        4
    syscall 
    j       end

print_dn:
    la      $a0,        dn                  # printf("DN\n");
    li      $v0,        4
    syscall 
    j       end

print_hd:
    la      $a0,        hd                  # printf("HD\n");
    li      $v0,        4
    syscall 
    j       end

end:
    li      $v0,        0
    jr      $ra                             # return 0



.data
prompt:
    .asciiz"Enter a mark: "
fl: 
    .asciiz"FL\n"
ps: 
    .asciiz"PS\n"
cr: 
    .asciiz"CR\n"
dn: 
    .asciiz"DN\n"
hd: 
    .asciiz"HD\n"
