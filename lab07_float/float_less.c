// Compare 2 floats using bit operations only

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "floats.h"

int is_normal(float_components_t* f) {
    if (f->exponent > 0 && f->exponent < 256) {
        return 1;
    }

    return 0;
}

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    // PUT YOUR CODE HERE

    float_components_t f1 = float_bits(bits1);
    float_components_t f2 = float_bits(bits2);

    if (is_nan(f1) || is_nan(f2)) {
        return 0;
    }

    if (f1.sign != f2.sign) {
        if (f1.sign == 1 && f1.exponent != 0) {
            return 1;
        } else {
            return 0;
        }
    }

    if (f1.exponent != f2.exponent) {
        if (f1.sign == 0) {
            if (f1.exponent < f2.exponent) {
                return 1;
            } else {
                return 0;
            }
        }
        if (f1.sign == 1) {
            if (f1.exponent > f2.exponent) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    if (f1.fraction != f2.fraction) {
        if (f1.sign == 0) {
            if (f1.fraction < f2.fraction) {
                return 1;
            } else {
                return 0;
            }
        }
        if (f1.sign == 1) {
            if (f1.fraction > f2.fraction) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    return 0;
}

#define N_BITS 32
#define SIGN_BIT 31
#define EXPONENT_HIGH_BIT 30
#define EXPONENT_LOW_BIT 23
#define FRACTION_HIGH_BIT 22
#define FRACTION_LOW_BIT 0

#define EXPONENT_OFFSET 127
#define EXPONENT_INF_NAN 0xFF

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    // PUT YOUR CODE HERE
    float_components_t res = {};

    uint32_t SIGN_MASK = 0x1;
    uint32_t EXPONENT_MASK = 0xff;
    uint32_t FRACTION_MASK = 0x7fffff;

    res.sign = (f & (SIGN_MASK << SIGN_BIT)) >> SIGN_BIT;

    res.exponent = (f & (EXPONENT_MASK << EXPONENT_LOW_BIT)) >> EXPONENT_LOW_BIT;

    res.fraction = (f & (FRACTION_MASK << FRACTION_LOW_BIT)) >> FRACTION_LOW_BIT;

    return res;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    // PUT YOUR CODE HERE

    return f.exponent == EXPONENT_INF_NAN && f.fraction != 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    // PUT YOUR CODE HERE

    return f.exponent == EXPONENT_INF_NAN && f.fraction == 0 && f.sign == 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    // PUT YOUR CODE HERE

    return f.exponent == EXPONENT_INF_NAN && f.fraction == 0 && f.sign == 1;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    // PUT YOUR CODE HERE

    return f.exponent == 0 && f.fraction == 0;
}