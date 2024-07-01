#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matchbox.h"

#ifdef main
#undef main
#endif

#ifdef num_packed_bytes
#undef num_packed_bytes
#endif

#define BYTES_PER_LINE 16

size_t num_packed_bytes(size_t sequence_length) {
    // This is equivalent to ceil(sequence_length / 8)
    return (sequence_length + 7) / 8;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    struct packed_matchbox matchbox = pack_matchbox(argv[1]);

    printf("Sequence length: %d\n", matchbox.sequence_length);
    
    int i;
    for (i = 0; i < num_packed_bytes(matchbox.sequence_length); i++) {
        printf("%02x", matchbox.packed_bytes[i]);

        if (i % BYTES_PER_LINE == BYTES_PER_LINE - 1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }

    if (i % BYTES_PER_LINE != 0) {
        printf("\n");
    }

    if (matchbox.packed_bytes != NULL) {
        free(matchbox.packed_bytes);
    }

    return 0;
}




