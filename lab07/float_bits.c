// Extract the 3 parts of a float using bit operations only

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

int main(int argc, char* argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        union overlay input;

        input.f = atof(argv[arg]);
        float_components_t c = float_bits(input.u);

        printf("float_bits(%.9g) returned\n", input.f);
        printf("sign=0x%x\n", c.sign);
        printf("exponent=0x%02x\n", c.exponent);
        printf("fraction=0x%06x\n", c.fraction);

        printf("is_nan returned %d\n", is_nan(c));
        printf("is_positive_infinity returned %d\n", is_positive_infinity(c));
        printf("is_negative_infinity returned %d\n", is_negative_infinity(c));
        printf("is_zero returned %d\n", is_zero(c));
    }

    return 0;
}
