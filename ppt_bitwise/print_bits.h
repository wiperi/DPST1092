// header file so we use print_bits in several examples
#ifndef PRINT_BITS_H
#define PRINT_BITS_H

#include <stdint.h>
void print_bits(uint64_t value, int how_many_bits);

#endif

#include <stdint.h>
#include <stdio.h>

// extract the nth bit from a value
int get_nth_bit(uint64_t value, int n) {
    // shift the bit right n bits
    // this leaves the n-th bit as the least significant bit
    uint64_t shifted_value = value >> n;

    // zero all bits except the the least significant bit
    int bit = shifted_value & 1;

    return bit;
}

// print the bottom how_many_bits bits of value
void print_bits(uint64_t value, int how_many_bits) {
    // print bits from most significant to least significant

    for (int i = how_many_bits - 1; i >= 0; i--) {
        int bit = get_nth_bit(value, i);
        printf("%d", bit);
    }
    printf("\n");
}