#include <stdio.h>

void print_bit(unsigned int val) {
    int len_val = sizeof(val) * 8;
    for (int i = len_val - 1; i >= 0; i--) {
        int bit = (val >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}


unsigned int reverse(unsigned int val) {

    // 0001
    // 1000

    unsigned int res = 0;
    int len_val = sizeof(val) * 8;
    int digit = 0;
    for (int i = 0; i < len_val; i++) {
        // extract digit
        digit = (val >> i) & 1;

        // set digit
        res |= (digit << (len_val - 1 - i));
    }

    return res;
}

int main(int argc, char* argv[], char* envp[]) {

    unsigned int val = 0xafffffff; // Example value

    unsigned int reversed_val = reverse(val);

    printf("Original value in binary: ");
    print_bit(val);

    printf("Reversed value in binary: ");
    print_bit(reversed_val);
    return 0;
}