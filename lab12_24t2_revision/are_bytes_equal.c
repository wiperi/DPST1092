#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const* argv[]) {
    
    FILE* file_a = fopen(argv[1], "r");

    fseek(file_a, atoi(argv[2]), SEEK_SET);

    int char_a = fgetc(file_a);

    FILE* file_b = fopen(argv[3], "r");

    fseek(file_b, atoi(argv[4]), SEEK_SET);

    int char_b = fgetc(file_b);

    if (char_a == char_b) {
        printf("byte %d in %s and byte %d in %c are the same\n", atoi(argv[2]),
               argv[1], atoi(argv[4]), argv[3]);
    } else {
        printf("byte %d in %s and byte %d in %c are not the same\n",
               atoi(argv[2]), argv[1], atoi(argv[4]), argv[3]);
    }

    return 0;
}
