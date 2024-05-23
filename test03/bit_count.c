// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    // PUT YOUR CODE HERE

    int res = 0;
    for (int i = 0; i < 64; i++) {
        int digit = (value >> i) & 1;

        if (digit) {
            res++;
        }
    }

    return res;
}
