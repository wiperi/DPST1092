#include "float_exp.h"

// given the 32 bits of a float return the exponent
uint32_t float_exp(uint32_t f) {

    uint32_t mask = (1 << 8) - 1;

    mask <<= 22;

    return mask & f;
}
