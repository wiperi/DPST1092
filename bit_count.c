#include <stdio.h>

void print_bit(int n) {
    for (int i = 0; i < 32; i++) {
        printf("%d", (n >> (32 - 1- i)) & 1);
    }
}

int main(int argc, char* argv[], char* envp[]) {
    int a = 0xffffff0f;

    print_bit(a);
}