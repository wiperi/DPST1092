#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {

    // range from -128 to 127 but extended ascii can range from 0 to 255
    char ch = 255;

    while (ch != EOF) {
        // (ch = 255) == (ch = 0b11111111) == (ch = -1)
        printf("Input: %c %d\n", ch, ch);
    }

    printf("eixt.\n");
}