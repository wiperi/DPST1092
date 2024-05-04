#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>.\n", argv[0]);
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");

    char window[4] = {};
    int i = 0;

    // while (has left to read()) {

    //     extend window

    //     while (need to shrink()) {
    //         shrink
    //     }
    // }

    int ch;
    while ((ch = fgetc(file)) != EOF) {

        if (isprint(ch)) {
            window[i++] = ch;
        } else {
            i = 0;
        }

        if (i == 4) {
            // window is fufilled, print the string
            i = 0;
            while (i < 4) {
                putchar(window[i]);
                i++;
            }
            i = 0;

            while ((ch = fgetc(file)) != EOF && isprint(ch)) {
                putchar(ch);
            }
            printf("\n");
        }
    }

    fclose(file);

    return 0;
}