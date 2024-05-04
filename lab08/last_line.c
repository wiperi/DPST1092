#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");

    int ch;
    int bias = 0;
    int start = 0;
    while (1) {
        if (fseek(file, -1 * bias, SEEK_END) == -1) {
            fseek(file, -1 * --bias, SEEK_END);
            break;
        }

        ch = fgetc(file);
        if (isprint(ch)) {
            start = 1;
        }
        if (start && !isprint(ch)) {
            break;
        }

        bias++;
    }

    while ((ch = fgetc(file)) != EOF && isprint(ch)) {
        putchar(ch);
    }
    if (ch != '\n') {
        printf("\n");
    }
}