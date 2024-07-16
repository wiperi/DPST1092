#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file name> <number1> <number2>...\n", argv[0]);
        exit(1);
    }

    // open file
    char* file_name = argv[1];
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        perror(file_name);
        return 1;
    }

    // write in numbers
    for (int i = 2; i < argc; i++) {
        int num = atoi(argv[i]);
        if (num < 0 || num > 255) {
            printf("Numbers should in the range 0..255\n");
            return 1;
        }

        fputc(num, file);
    }
    fclose(file);
    
    return 0;
}