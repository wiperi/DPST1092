#include <stdio.h>

int main(void) {
    printf("The unicode code point U+1F600 encodes in UTF-8\n");
    printf("as 4 bytes: 0xF0 0x9F 0x98 0x80\n");
    printf("We can output the 4 bytes like this: \xF0\x9F\x98\x80 (UTF-8)\n");
    printf("Or like this: ");
    putchar(0xF0);
    putchar(0x9F);
    putchar(0x98);
    putchar(0x80);
    putchar('\n');
    printf("Or like this: \U0001F600 (UTF-32)\n");
    // UNICODE code point less than 0x10000 (ie the BMP) can be encoded with
    // \uXXXX (lowercase u) with only 4 hex digits
    // \U must always be followed by 8 hex digits
}
