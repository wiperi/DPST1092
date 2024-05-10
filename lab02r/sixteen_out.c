// Convert a 16-bit signed integer to a string of binary digits

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N_BITS 16

char* sixteen_out(int16_t value);

int main(int argc, char* argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char* bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char* sixteen_out(int16_t value) {

    // value: 0001
    // bits:  "0001"

    char* res = malloc(sizeof(char) * 17);

    for (int i = 0; i < 16; i++) {

        int digit = value & (1 << i);

        if (digit) {
            res[15 - i] = '1';
        } else {
            res[15 - i] = '0';
        }
    }
    res[16] = '\0';

    return res;
}
