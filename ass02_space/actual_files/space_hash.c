///////////////////////////////////////////////////////////////////////////////
// DPST1092 24T2 --- Assignment 2: `space', a simple file archiver          //
//                                                                            //
//                                                                            //
///////////////////// YOU DO NOT NEED TO MODIFY THIS FILE. /////////////////////

////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////

#include <stdint.h>

// DO NOT CHANGE THIS FUNCTION - use it to calculate galaxy hashes (subsets 1, 2, and 3)

//
// The djb2-xor hash: hash(i) = hash(i - 1) * 33 ^ str[i];
// For more information  http://www.cse.yorku.ca/~oz/hash.html
//
// galaxy_hash(), given the current hash value and a byte value, returns the new hash value
// An galaxy hash is calculated by calling galaxy_hash once for each byte in the galaxy except the last byte
// current_hash_value should be zero, for the first byte in the galaxy

uint8_t galaxy_hash(uint8_t current_hash_value, uint8_t byte_value) {
    return ((current_hash_value * 33) & 0xff) ^ byte_value;
}

////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
