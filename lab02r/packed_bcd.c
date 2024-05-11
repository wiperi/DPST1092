#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char* argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long) packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    // PUT YOUR CODE HERE

    int res = 0;

    for (int i = 0; i < (32 / 4); i++) {

        int weight = 1;
        for (int j = 0; j < i; j++) {
            weight *= 10;
        }

        int digit = (packed_bcd_value >> (i * 4)) & 0xf;
        res += weight * digit;
    }

    return res;

}