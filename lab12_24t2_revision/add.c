#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t make_add(uint32_t d, uint32_t s, uint32_t t) {

    d &= 0x1f;
    s &= 0x1f;
    t &= 0x1f;

    uint32_t res = 0;

    res |= (1 << 5);

    res |= (d << 11);

    res |= (t << 16);

    res |= (s << 21);

    return res;

}
