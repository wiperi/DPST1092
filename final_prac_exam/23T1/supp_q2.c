// DPST1092 ... supp, question 2
// Assuming that the right-most (least significant) bit is labelled 0,
// and the left-most (most significant) bit is labelled 31,
// set bit 11 to 1, and bit 15 to 0.

#include <stdint.h>

uint32_t supp_q2(uint32_t x) {
    // TODO: add/modify code here

    // clean bit 11 and 15
    uint32_t mask = 1 << 11;
    x &= (~mask);
    mask = 1 << 15;
    x &= (~mask);

    // set bit 11
    x |= (1 << 11);


    return x;
}
