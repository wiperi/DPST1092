#include <stdio.h>
#include <stdint.h>

// Given an UTF-8 string, return the index of the first invalid byte.
// If there are no invalid bytes, return -1.

// Do NOT change this function's return type or signature.
int invalid_utf8_byte(char *utf8_string) {
    
    // TODO: implement this function

    uint8_t ch;
    int i = 0;
    while (utf8_string[i] != '\0')
    {
        ch = utf8_string[i];

        // is head valid?
        int tail = 0;
        printf("%c %x\n", ch, ch);
        if ((ch >> 7) == 0) {
            ;
        } else if ((ch >> 3) == 0b11110) {
            tail = 3;
        } else if ((ch >> 4) == 0b1110) {
            tail = 2;
        } else if ((ch >> 5) == 0b110) {
            tail = 1;
        } else {
            // invalid
            return i;
        }

        // is tail valid?
        if (tail != 0) {
            for (int j = 0; j < tail; j++) {
                i++;
                ch = utf8_string[i];

                if ((ch >> 6) == 0b10) {
                    ;
                } else {
                    // invalid
                    return i;
                }
            }
        }

        i++;
    }
    
    return -1;
}
