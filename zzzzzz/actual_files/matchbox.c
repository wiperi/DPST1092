#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matchbox.h"

#define BYTE_LENGTH 8


struct packed_matchbox pack_matchbox(char *filename) {
    // TODO: complete this function!
    // You may find the definitions in matchbox.h useful.

    struct packed_matchbox matchbox = {
        .sequence_length = 0,
        .packed_bytes = NULL
    };
    
    return matchbox;
}
