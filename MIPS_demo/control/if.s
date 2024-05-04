.text

main:
    # assuming i in $t0,
    # assuming n in $t1...
    bge     $t0,    0,      else1   # if i < 0, goto else1
    sub     $t1,    $t1,    $t0     # n = n - i
    goto    end1
else1:
    add     $t1,    $t1,    $t0     # n = n + i
end1:
