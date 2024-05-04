    # using a frame pointer to handle stack growing during function execution

    # What does function pointer do?
    # begin: it just push in a new word and store a pointer pointing to it to $fp, 
    # and store the previous $fp address into the *($fp)
    # end: jump back to the begin

example_of_frame_pointer_easy:
    begin                           # move frame pointer
    push    $ra                     # save $ra on stack

    li      $v0,    5               # scanf("%d", &length);
    syscall 

    mul     $v0,    $v0,        4   # calculate array size
    sub     $sp,    $sp,        $v0 # move stack_pointer down to hold array
    # ... more code ...
    add     $sp,    $sp,        $v0 # move back the stack pointer, like free()


    pop     $ra                     # restore $ra
    end     
    jr      $ra                     # return


example_of_frame_pointer_hard:
    # prologue
    sub     $sp,    $sp,        8
    sw      $fp,    4($sp)
    sw      $ra,    0($sp)
    add     $fp,    $sp,        8

    li      $v0,    5               # scanf("%d", &length);
    syscall 
    mul     $t0,    $v0,        4
    sub     $sp,    $sp,        $t0 # int array[length];
    # ... more code ...
    add     $sp,    $sp,        $v0 # free(array)

    # epilogue
    lw      $ra,    -4($fp)
    move    $sp,    $fp
    lw      $fp,    0($fp)

    jr      $ra
