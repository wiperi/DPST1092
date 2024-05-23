// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t bit_swap(uint64_t x) {
    // Mask for even bits: 0xAAAAAAAAAAAAAAAA (binary: 10101010...10)
    uint64_t even_bits = x & 0xAAAAAAAAAAAAAAAA;
    // Mask for odd bits: 0x5555555555555555 (binary: 01010101...01)
    uint64_t odd_bits = x & 0x5555555555555555;
    
    // Shift even bits right by 1 to swap with odd bits
    even_bits >>= 1;
    // Shift odd bits left by 1 to swap with even bits
    odd_bits <<= 1;
    
    // Combine the swapped bits
    return even_bits | odd_bits;
}