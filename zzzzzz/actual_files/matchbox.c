#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matchbox.h"

#define BYTE_LENGTH 8


struct packed_matchbox pack_matchbox(char *filename) {
    // TODO: complete this function!
    // You may find the definitions in matchbox.h useful.

    // read the byte sequence length
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen() error");
        exit(1);
    }

    uint8_t first_byte = fgetc(file);
    uint8_t second_byte = fgetc(file);
    uint16_t seq_len = (first_byte) | (second_byte << 8);

    int arr_len = 0;
    if (seq_len % 8 == 0) {
        arr_len = seq_len / 8;
    } else {
        arr_len = seq_len / 8 + 1;
    }

    // read the sequence
    uint8_t* arr = malloc(arr_len * sizeof(uint8_t));

    int ch;
    for (int arr_i = 0; arr_i < arr_len; arr_i++) {

        uint8_t pack = 0;
        for (int j = 7; j >= 0; j--) {
            ch = fgetc(file);
            if (ch == '1') {
                pack |= (1 << j);
            } else if (ch == EOF) {
                break;
            }
        }
        arr[arr_i] = pack;
    }

    struct packed_matchbox matchbox = {
        .sequence_length = seq_len,
        .packed_bytes = arr,
    };
    
    return matchbox;
}
