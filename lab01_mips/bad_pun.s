.data
string:
    .asciiz"Well, this was a MIPStake!\n"

.text
main:
    la      $a0,    string                  # ... pass address of string as argument
    li      $v0,    4                       # ... 4 is printf "%s" syscall number
    syscall 
    # return 0
    li      $v0,    0
    jr      $ra
