// Multiply a float by 2048 using bit operations only

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "floats.h"

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

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    // PUT YOUR CODE HERE

    // if (f is normal) {
    //     if (f.exp + 11 and not overflow) {
    //         return f;
    //     } else {
    //         if (f.exp + 11 and overflow) {
    //             return inf
    //         }
    //     }
    // } else {
    //     // f is special number
    // }

    float_components_t fl = float_bits(f);

    if (fl.exponent != EXPONENT_INF_NAN && fl.exponent != 0) {
        // f is normalized
        if (fl.exponent + 11 < 256) {
            // fl.exp + 11 not overflow
            fl.exponent += 11;

            // before building bitpattern it is important to first reset the previous pattern
            f &= ~(0xff << EXPONENT_LOW_BIT);
            
            f |= (fl.exponent << EXPONENT_LOW_BIT);
            return f;
        } else {
            // fl.exp + 11 overflow
            f |= (0xff << EXPONENT_LOW_BIT);
            f &= ~(0x7fffff);
            return f;
        }
    } else {
        // f is special number
        return f;
    }

    return 42;
}

int main(int argc, char* argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        union overlay input, result;

        input.f = atof(argv[arg]);
        result.u = float_2048(input.u);
        printf("%.9g\n", result.f);
    }

    return 0;
}
