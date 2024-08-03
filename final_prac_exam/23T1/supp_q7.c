// DPST1092 23T1 ... supp exam, question 7

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int get_format(uint8_t ch) {
    if ((ch >> 7) == 0) {
        return 1;
    } else if ((ch >> 5) == 0b110) {
        return 2;
    } else if ((ch >> 4) == 0b1110) {
        return 3;
    } else if ((ch >> 3) == 0b11110) {
        return 4;
    }
    perror("format error");
    exit(1);
}

// str is a UTF-8 encoded string containing valid UTF-8 characters.
// returns a new string with only unicode
// characters that are encoded in the given number of bytes

char *supp_q7(char *str, int bytes) {
    char *new_str = malloc(strlen(str) + 1);

    int i = 0;
    int j = 0;
    int format = 0;
    while (i < strlen(str)) {
        uint8_t ch = str[i];

        format = get_format(ch);
        // printf("i = %d, ch = %0x, format = %d\n", i, ch, format);

        if (format == bytes) {
            // copy to new str
            for (int k = 0; k < format; k++)
            {
                new_str[j++] = str[i++];
            }
        } else {
            // ignore
            i += format;
        }
    }
    new_str[j] = '\0';

    return new_str;
}
