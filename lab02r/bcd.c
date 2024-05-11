#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int bcd(int bcd_value);

int main(int argc, char* argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

    // PUT YOUR CODE HERE

    int res = 0;
    for (int i = 0; i < 4; i++) {
        res += (0xff << i * 8) & bcd_value;
    }

    return res;
}
