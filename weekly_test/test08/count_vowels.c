#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Count the number of vowels in the file
    int vowelCount = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isVowel(ch)) {
            vowelCount++;
        }
    }

    // Close the file
    fclose(file);

    // Print the vowel count
    printf("Number of vowels in the file: %d\n", vowelCount);

    return 0;
}