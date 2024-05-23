// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    // PUT YOUR CODE HERE

    // 10 01
    // 01 01

    // 0 2 4 ... 62
    // 1 3 5 ... 63
    uint64_t res = 0;
    for (int i = 0; i < 64; i += 2) {
        
        uint64_t first_digit = 0;
        first_digit |= ((1 << i) & value);

        uint64_t sec_digit = 0;
        sec_digit |= ((1 << (i + 1)) & value);

        res |= (first_digit << 1);
        res |= (sec_digit >> 1);
    }

    return res;
}
