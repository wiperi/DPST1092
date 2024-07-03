#include <stdio.h>
#include <stdlib.h>

int is_vowel(int ch) {
    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}

int main(int argc, char *argv[], char *envp[]) {

    if (argc != 3) {
        printf("Usage: %s <file_path> <output_file_path>\n", argv[0]);
        return 1;
    }
    
    
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen failed: ");
        exit(1);
    }

    int ch;
    FILE* output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("fopen failed: ");
        exit(1);
    }

    while ((ch = fgetc(file)) != EOF) {
        if (!is_vowel(ch)) {
            fputc(ch, output_file);
        }
    }

    fclose(file);

    fclose(output_file);

    return 0;
}