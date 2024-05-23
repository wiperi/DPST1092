// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    // PUT YOUR CODE HERE

    // 1234 to 3412

    uint16_t mask = 0xff;

    uint16_t res = 0;

    res |= ((mask << 8) & value) >> 8;
    res |= (mask & value) << 8;



    return res;
}
