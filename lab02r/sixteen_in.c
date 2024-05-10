// Convert string of binary digits to 16-bit signed integer

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_BITS 16

int16_t sixteen_in(char* bits);

int main(int argc, char* argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char* bits) {

    // bits: "1010"
    // res:   1010

    int16_t res = 0;

    for (int i = 0; bits[i] != '\0'; i++) {

        if (bits[i] == '1') {
            // set i the digit
            int16_t mask = 1 << (16 - i - 1);
            res = res | mask;
        } else {
            continue;
        }
    }

    return res;
}
