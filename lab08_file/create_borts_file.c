#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

int main(int argc, char *argv[], char *envp[]) {
    
    if (argc != 4) {
        printf("Usage: %s <file name> <start number> <end number>", argv[0]);
        return 0;
    }

    FILE *file = fopen(argv[1], "w");
    
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    assert(start <= end);
    assert(end < (1 << 16));

    for (uint16_t n = start; n <= end; n++) {
        // write in n as a two byte big endian

        // sup 0x1234, in memory: 0x1234
        fputc(n >> 8, file);
        fputc(n & 0xFF, file);
    }

    fclose(file);

    return 0;
}