//* // // // // // DO NOT MODIFY THIS FILE // // // // // // *//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef main
#undef main
#endif

#define BUF_INIT_SIZE 1024

int invalid_utf8_byte(char* utf8_string);

int main(int argc, char* argv[]) {

    FILE* file = fopen(argv[1], "r");

    char* buf = malloc(BUF_INIT_SIZE);
    assert(buf != NULL);

    int buf_size = BUF_INIT_SIZE;
    int buf_used = 0;

    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (buf_used == buf_size - 1) {
            buf_size *= 2;
            buf = realloc(buf, buf_size);
            assert(buf != NULL);
        }
        buf[buf_used++] = c;
    }

    buf[buf_used] = '\0';

    int result = invalid_utf8_byte(buf);

    if (result == -1) {
        printf("No invalid bytes found.\n");
    } else {
        printf("Invalid byte found at index %d.\n", result);
    }

    return 0;
}

int invalid_utf8_byte(char* utf8_string) {

    // TODO: implement this function

    for (int i = 0; utf8_string[i] != '\0'; i++) {

        unsigned int ch = utf8_string[i];

        if ((ch >> 7) == 0) {
            // 0xxx = good
            continue;
        } else if ((ch >> 6) == 0b10) {
            // sole 10xx = not good
            return i;
        } else {
            // 1xxx = there are followings
            int k = 7;
            int len = -1;
            while (k >= 0) {
                if (((ch >> k) & 1) == 1) {
                    len++;
                } else {
                    break;
                }
                k--;
            }

            for (int j = 0; j < len; j++) {
                // check successive byte
                i++;
                ch = utf8_string[i];
                printf("%02x\n", ch);

                if ((ch >> 6) == 0b10) {
                    continue;
                } else {
                    return i;
                }
            }
        }
    }

    return -1;
}
