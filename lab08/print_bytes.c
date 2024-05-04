#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        exit(1);
    }

    char* file_name = argv[1];

    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        perror(file_name);
        return 1;
    }

    int ch = 0;
    int i = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (isprint(ch)) {
            printf("byte %4d: %3d 0x%2.2x '%c'\n", i, ch, ch, ch);
        } else {
            printf("byte %4d: %3d 0x%2.2x     \n", i, ch, ch);
        }
        i++;
    }

    fclose(file);
}