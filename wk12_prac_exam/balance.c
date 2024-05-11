#include <stdio.h>
#include <stdlib.h>

int balance(int x) {
    // 0b 0001000001010000 0000110000000100
    int upper_count = 0;
    int lower_count = 0;
    int mask = 1;
    mask = (mask << 16) - 1;
    int lower = x & mask;
    int upper = x >> 16;
    upper = upper & mask;

    for (int i = 0; i < 16; i++) {
        if ((lower >> i) & 1) {
            lower_count++;
        }
        if ((upper >> i) & 1) {
            upper_count++;
        }
    }

    if (upper_count == lower_count) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Given a 32 bit pattern, if same amount of '1' occur in both 0 - 15th digit and 16 - 31th digit.
 * Return 1, otherwise, return 0
 */
int my_balance(int x) {
    int mask_up = 1 << 16;
    int mask_down = 1;

    int down_count = 0;
    int up_count = 0;
    for (int i = 0; i < 16; i++)
    {
        int digit = mask_down << (i * 1) & x;
        if (digit != 0) {
            down_count++;
        }

        digit = mask_up << (i * 1) & x;
        if (digit != 0) {
            up_count++;
        }
    }

    return down_count == up_count;
    
}

int main(int argc, char* argv[]) {

    int x = atoi(argv[1]);
    printf("%d", my_balance(x));
    printf("%d", balance(x));
}