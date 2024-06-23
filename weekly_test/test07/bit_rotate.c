#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    // Ensure n_rotations is within [0, 15]
    n_rotations = ((n_rotations % 16) + 16) % 16;

    // If no rotation is needed, return the bits as is
    if (n_rotations == 0) {
        return bits;
    }

    // Perform left rotation
    uint16_t res = (bits << n_rotations) | (bits >> (16 - n_rotations));

    return res;
}
