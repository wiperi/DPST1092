.text   
main:       
    # this program are not runable, just for demo
    
    # 3 difference use of lw
    # same for sw, sh, sb
    lw      $a0,    0x12345678
    lw      $a0,    label_1

    li      $t0,    label_1
    lw      $a0,    ($t0)



.data   
label_1:    .space  1