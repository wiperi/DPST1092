#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

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

    // find last char, if ther is only one char in file, return
    if (fseek(file, -1, SEEK_END) < 0) {
        return 0;
    }
    char last_char = fgetc(file);

    // if last char is LF, read from the second last char
    if (last_char == '\n') {
        fseek(file, -2, SEEK_CUR);
    } else {
        fseek(file, -1, SEEK_CUR);
    }

    // read backward, stop until reach LF or go beyond the begining or reach the beginning
    int ch;
    while ((ch = fgetc(file)) != '\n') {
        
        if (fseek(file, -2, SEEK_CUR) < 0) {
            // go beyond the beginning
            rewind(file);
            break;
        }

        if (ftell(file) == 0) {
            // reach the beginning
            break;
        }
    }

    // print last line
    while ((ch = getc(file)) != EOF) {
        putchar(ch);
    }

    return 0;
}