.text

logic_and:
    # assume i in $t0
    # assume n in $t1
    bge     $t0,    0,      else1
    blt     $t1,    42,     else1
    sub     $t1,    $t1,    $t0
    j       end1
else1:
    add     $t1,    $t1,    $t0
end1:
    jr      $ra

logic_or:
    # assume i in $t0
    # assume n in $t1
    blt     $t0,    0,      else1
    bge     $t1,    42,     else1
    sub     $t1,    $t1,    $t0
    j       end1
else1:
    add     $t1,    $t1,    $t0
end1:
    jr      $ra
