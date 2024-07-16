// Print out a float.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

char* int_to_string(uint32_t n) {

    char* res = calloc(1024, 1);
    int i = 0;

    int q = 10;
    while (n != 0) {
        int digit = n % q;
        res[i++] = digit + '0';
        n /= 10;
    }
    res[i] = '\0';

    return res;
}

//
// float_print is given the bits of a float as a uint32_t
// it prints out the float in the same format as "%.9g\n"
// using only putchar & puts
//
void float_print(uint32_t bits) {
    // PUT YOUR CODE HERE

    float_components_t f = float_bits(bits);

    if (f.sign == 1) {
        putchar('-');
    }
    
    // Nan
    if (is_nan(f)) {
        puts("nan");
    }

    uint32_t frac = (1 << 23);
    frac |= f.fraction;
    printf("%x\n", frac);
    puts(int_to_string(frac));

    
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
