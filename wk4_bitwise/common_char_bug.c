// most platforms: char is signed (-128..127)
// • loop will incorrectly exit for a byte containing 0xFF
// • rare platforms: char is unsigned (0..255)
// • loop will never exit

#include <stdio.h>

int main(int argc, char* argv[]) {

    char c;
    int input = 0xff;

    c = input;

    printf("c = %d,  input = %d\n", c, input); // unsigned cast to sign

    if (c == EOF) {
        printf("program exit, last input was: %c\n", input);
    }
}