.text

main:
    li      $t0,    0           # i in $t0
    li      $t1,    0           # n in $t1
loop:
    bge     $t0,    5,      end # if t0 > 5, jump to end
    add     $t1,    $t1,    $t0
    addi    $t0,    $t0,    1
    j       loop
end:
