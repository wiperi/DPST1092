#include <stdio.h>
#include <stdlib.h>

int is_ascii(int ch) {
    return (ch & 0x80 ) == 0;
}

int main(int argc, char* argv[]) {
    
    FILE* file = fopen(argv[1], "r");
    
    int ch;
    int count = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (!is_ascii(ch)) {
            printf("%s: byte %d is non-ASCII\n", argv[1], count);
            exit(0);
        }

        count++;
    }

    printf("%s is all ASCII\n", argv[1]);

    return 0;
    
}