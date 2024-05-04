    # Reads a 4-byte value and reverses the byte order, then prints it

    ########################################################################
    # .TEXT <main>
main:
    # Locals:
    #	- $s0: int network_bytes
    #	- $s1: int computer_bytes
    #	- Add your registers here!


    li      $v0,    5           # scanf("%d", &x);
    syscall 
    move    $s0,    $v0         # s0 = network_bytes

    #       
    # Your code here!
    #       
    li      $s1,    0           # int32_t computer_bytes = 0;
    li      $s2,    0xff        # uint32_t byte_mask = 0xFF

    and     $t0,    $s0,    $s2 # s0 & s2
    sll     $t0,    $t0,    24  # << 24
    or      $s1,    $s1,    $t0 # |= s1

    sll     $t0,    $s2,    8   # s2 << 8
    and     $t0,    $s0,    $t0 # & s0
    sll     $t0,    $t0,    8   # << 8
    or      $s1,    $s1,    $t0 # |= s1

    sll     $t0,    $s2,    16  # s2 << 16
    and     $t0,    $s0,    $t0 # & s0
    srl     $t0,    $t0,    8   # >> 8
    or      $s1,    $s1,    $t0 # |= s1

    sll     $t0,    $s2,    24  # s2 << 24
    and     $t0,    $s0,    $t0 # & s0
    srl     $t0,    $t0,    24  # >> 24
    or      $s1,    $s1,    $t0 # |= s1

    move    $a0,    $s1         # printf("%d\n", x);
    li      $v0,    1
    syscall 

    li      $a0,    '\n'        # printf("%c", '\n');
    li      $v0,    11
    syscall 

main__end:
    li      $v0,    0           # return 0;
    jr      $ra
