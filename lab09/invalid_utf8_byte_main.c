//* // // // // // DO NOT MODIFY THIS FILE // // // // // // *//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef main
#undef main
#endif

#define BUF_INIT_SIZE 1024

int invalid_utf8_byte(char *utf8_string);

int main(void) {
    char *buf = malloc(BUF_INIT_SIZE);
    assert(buf != NULL);

    int buf_size = BUF_INIT_SIZE;
    int buf_used = 0;

    int c;
    while ((c = getchar()) != EOF && c != '\n') {
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
