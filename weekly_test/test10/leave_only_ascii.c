#include <stdio.h>
#include <stdlib.h>

int is_ascii(int ch) {
    return (ch & 0x80) == 0;
}

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    long file_size = 0;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char content[file_size];

    int ch;
    int count = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (is_ascii(ch)) {
            content[count] = ch;
            count++;
        }
    }

    fclose(file);

    file = fopen(argv[1], "w");

    for (long i = 0; i < count; i++) {
        fputc(content[i], file);
    }

    return 0;
}