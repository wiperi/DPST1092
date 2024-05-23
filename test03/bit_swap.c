// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t bit_swap(uint64_t x) {
    uint64_t even_bits = x & 0xAAAAAAAAAAAAAAAA;
    uint64_t odd_bits = x & 0x5555555555555555;
    
    even_bits >>= 1;
    odd_bits <<= 1;
    
    return even_bits | odd_bits;
}