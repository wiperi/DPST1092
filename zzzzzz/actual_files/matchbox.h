#ifndef __MATCHBOX_H
#define __MATCHBOX_H

#include <stdint.h>
#include <stddef.h>

struct packed_matchbox {
    uint16_t sequence_length;
    uint8_t *packed_bytes;
};

// This provided function can be used to determine the number of bytes
// required to store a given number of bits.
size_t num_packed_bytes(size_t sequence_length);

// You will need to implement this function in matchbox.c
struct packed_matchbox pack_matchbox(char *filename);

#endif // __MATCHBOX_H
