// generate the encoded binary for an addi instruction, including opcode and operands

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "addi.h"

// #include "C:\Users\15617\Documents\92_MyGithub\CSAPP\ppt_bitwise\print_bits.h" // debug

// return the encoded binary MIPS for addi $t,$s, i
uint32_t addi(int t, int s, int i) {

    assert(t >= 0 && t < 32);
    assert(s >= 0 && s < 32);
    assert(i < (1 << 16));

    uint32_t res = 0;

    // build opcode
    res = 0b001000 << 26;
    // print_bits(res, 32); // debug

    // build source
    res |= s << 21;
    // print_bits(res, 32); // debug

    // build dest
    res |= t << 16;
    // print_bits(res, 32); // debug

    // build imm val
    res |= (uint16_t) i;
    // res |= ((((unsigned) i) << 16) >> 16); // alternative
    // print_bits(res, 32); // debug

    return res;
}

int main(int argc, char const* argv[]) {
    addi(31, 31, -1);

    return 0;
}
