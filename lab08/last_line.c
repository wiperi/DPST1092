#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int try(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    try(argc, argv);
    return 0;

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

int try(int argc, char* argv[]) {

    // if (last char is \n) {
    //     read from second last char;
    // } else if (last char is not \n) {
    //     read from last char;
    // }
    // while (does not meet the preivous \n and
    //        does not reach the file beginning) {
    //     read;
    // }

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file: ");
        exit(1);
    }

    if (fseek(file, -1, SEEK_END) < 0) {
        perror("fseek() failed");
        exit(1);
    }
    char last_char = fgetc(file);

    if (last_char == '\n') {
        fseek(file, -2, SEEK_CUR);
    } else {
        fseek(file, -1, SEEK_CUR);
    }

    int ch;
    while ((ch = fgetc(file)) != '\n') {
        fseek(file, -2, SEEK_CUR);

        if (ftell(file) == 0) {
            break;
        }
    }

    while ((ch = getc(file)) != EOF) {
        putchar(ch);
    }

    return 0;
}