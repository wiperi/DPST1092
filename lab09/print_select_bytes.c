#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file name> <num> <num>...", argv[0]);
        exit(1);
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Failed to open file.");
        exit(1);
    }

    for (int i = 2; i < argc; i++) {

        int pos = atoi(argv[i]);
        fseek(file, pos, SEEK_SET);

        int ch = fgetc(file);

        if (isprint(ch)) {
            printf("%d - 0x%02X - '%c'\n", ch, ch, ch);
        } else {
            printf("%d - 0x%02X\n", ch, ch);
        }
    }
}