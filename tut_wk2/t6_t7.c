/**
 * Introduction:
 * 
 * set nth bit, unset nth bit
 */
#include <stdio.h>

void print_bit(unsigned char value) {
    for (int i = sizeof(value) * 8 - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

unsigned char unset_nth_bit(unsigned char value, unsigned char n) {

    if (n > (sizeof(value) * 8)) {
        return value;
    }

    value &= ~(1 << n);

    return value;
}

unsigned char set_nth_bit(unsigned char value, unsigned char n) {

    if (n > (sizeof(value) * 8)) {
        return value;
    }

    value |= (1 << n);

    return value;
}

int main(int argc, char *argv[], char *envp[]) {
    
    unsigned char res = 0xf;
    res = unset_nth_bit(res, 3);
    res = set_nth_bit(res, 7);

    print_bit(res);
}