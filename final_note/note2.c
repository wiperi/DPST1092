#include <stdio.h>
#include <stdint.h>

uint8_t rotate(uint8_t x, int n) {
    // left rotate n bit
    n %= 8;
    uint8_t res = (x << n) | (x >> (8 - n));
    return res;
}

void print_bit(uint64_t x, int n) {
    for (int i = 0; i < n; i++) {
        int a = (x >> (n - 1 - i)) & 01;
        printf("%d", a);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    uint8_t x = 0b10100111;
    print_bit(rotate(x, 11), 8);
}