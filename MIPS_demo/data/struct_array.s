# simple example of accessing struct within array within struct

# struct point {
#   int x;
#   int y;
# };
# 
# struct polygon {
#     int            degree;
#     struct point   vertices[6];
# };

OFFSET_POINT_X    = 0
OFFSET_POINT_Y    = 4
SIZEOF_POINT      = 8

OFFSET_POLYGON_DEGREE    = 0
OFFSET_POLYGON_VERTICES  = 4
SIZEOF_POLYGON           = 52 # 6 * sizeof(point) = 48, 48 + 4 =  52

main:
    push    $ra

    la   $a0, triangle
    jal  print_last_vertex                # print_last_vertex(&triangle);

    li   $v0, 0
    pop  $ra
    jr   $ra


print_last_vertex:
    # $a0: p
    # $t0: n
    # $t1: last
    # $t2..$t5: temporaries

    lw   $t2, OFFSET_POLYGON_DEGREE($a0)   # int n = p->degree - 1;
    addi $t0, $t2, -1

    # $t0 is (p->degree - 1)
    addi $t3, $a0, OFFSET_POLYGON_VERTICES # calculate &(p->vertices[n])
    mul  $t4, $t0, SIZEOF_POINT            
    add  $t1, $t3, $t4 # $t1 = p->vertices + ((p->degree - 1) * sizeof(point))


    lw   $a0, OFFSET_POINT_X($t1)          # printf("%d", last->x);
    li   $v0, 1
    syscall

    li   $a0, ','                          # putchar(',');
    li   $v0, 11
    syscall

    lw   $a0, OFFSET_POINT_Y($t1)          # printf("%d", last->y);
    li   $v0, 1
    syscall

    li   $a0, '\n'                         # putchar('\n');
    li   $v0, 11
    syscall

    jr   $ra

.data

# struct polygon triangle = {3, {{0,0}, {3,0}, {0,4}}};

triangle:
    .word 3
    .word 0,0, 3,0, 0,4, 0,0, 0,0, 0,0
