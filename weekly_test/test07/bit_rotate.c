#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {

    // 1001 1000 rotate 4

    // 0000 1111
    uint16_t r_mask = (1 << (n_rotations)) - 1;

    // 1111 0000
    uint16_t l_mask = ~r_mask;

    uint16_t res = 0;
    res |= (bits & r_mask) << n_rotations;
    res |= (bits & l_mask) >> (16 - n_rotations);
    
    return res;
}
