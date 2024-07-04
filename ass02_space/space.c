////////////////////////////////////////////////////////////////////////
// DPST1092 --- Assignment 2: `space', a simple file archiver
//
//
// Written by Tianyang Chen (z5567323) on 3/July/2024.
//
// 2024-03-08   v1.1    Team DPST1092

#include <assert.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "space.h"

// ADD ANY extra #defines HERE

// ADD YOUR FUNCTION PROTOTYPES (AND STRUCTS IF ANY) HERE

int hash_getc(FILE* file, uint8_t* hash);
uint64_t little_endian_to_uint(FILE* file, int n_bytes, uint8_t* hash);

// print the files & directories stored in galaxy_pathname (subset 0)
//
// if long_listing is non-zero then file/directory permissions, formats & sizes
// are also printed (subset 0)
//
// It is not necessary to check the hashes or magic numbers of stars in subset
// 0. Subset 0 tests will only use valid stars.

void list_galaxy(char* galaxy_pathname, int long_listing) {

    printf("list_galaxy called to list galaxy: '%s'\n", galaxy_pathname);

    if (long_listing) {
        printf("long listing with permissions & sizes specified\n");
    }
}

// check the files & directories stored in galaxy_pathname (subset 1)
//
// prints the files & directories stored in galaxy_pathname with a message
// either, indicating the hash byte is correct, or indicating the hash byte
// is incorrect, what the incorrect value is and the correct value would be

void check_galaxy(char* galaxy_pathname) {

    /**
     * check magic
     * format
     * perm
     * pathname len
     * pathname
     * content len
     * content
     */

    FILE* file = fopen(galaxy_pathname, "r");
    if (file == NULL) {
        fprintf(stderr, "%s: No such file or directory", galaxy_pathname);
        exit(1);
    }

    uint8_t hash = 0;
    int ch;

    // check magic
    ch = hash_getc(file, &hash);
    if (ch != 'c') {
        fprintf(stderr,
                "error: incorrect first star byte: 0x%x should be 0x63\n", ch);
        exit(1);
    }

    // check star format
    ch = hash_getc(file, &hash);
    switch (ch) {
    case '8':
    case '7':
    case '6':
        break;
    default:
        fprintf(stderr, "error: unknown star format: 0x%x\n", ch);
        exit(1);
        break;
    }

    // check permissions
    int permissions_invalid = 0;
    char permissions[10];
    for (int i = 0; i < 10; i++) {
        ch = hash_getc(file, &hash);
        permissions[i] = ch;

        if (i == 0) {
            switch (ch) {
                case '-':
                case 'd':
                    break;
                default:
                    permissions_invalid = 1;
                    break;
            }
        } else {
            switch (ch) {
                case '-':
                case 'r':
                case 'w':
                default:
                    permissions_invalid = 1;
                    break;
            }
        }
    }
    if (permissions_invalid) {
        fprintf(stderr, "error: invalid permission string %s\n", permissions);
        exit(1);
    }

    // check pathlen
    uint64_t pathlen = little_endian_to_uint(file, 2, &hash);
    printf("%lu\n", pathlen);

}

// extract the files/directories stored in galaxy_pathname (subset 1 & 3)

void extract_galaxy(char* galaxy_pathname) {

    printf("calling extract galaxy. extracting %s\n", galaxy_pathname);
}

// create galaxy_pathname containing the files or directories specified in
// pathnames (subset 2 & 3)
//
// if append is zero galaxy_pathname should be over-written if it exists
// if append is non-zero galaxys should be instead appended to galaxy_pathname
//                       if it exists
//
// format specifies the galaxy format to use, it must be one STAR_FMT_6,
// STAR_FMT_7 or STAR_FMT_8

void create_galaxy(char* galaxy_pathname, int append, int format,
                   int n_pathnames, char* pathnames[n_pathnames]) {

    // REPLACE THIS CODE PRINTFS WITH YOUR CODE

    printf("create_galaxy called to create galaxy: '%s'\n", galaxy_pathname);
    printf("format = %x\n", format);
    printf("append = %d\n", append);
    printf("These %d pathnames specified:\n", n_pathnames);
    for (int p = 0; p < n_pathnames; p++) {
        printf("%s\n", pathnames[p]);
    }
}

// ADD YOUR EXTRA FUNCTIONS HERE

int hash_getc(FILE* file, uint8_t* hash) {
    int ch = fgetc(file);
    *hash = galaxy_hash(*hash, ch);
    return ch;
}

uint64_t little_endian_to_uint(FILE* file, int n_bytes, uint8_t* hash) {

    assert(n_bytes <= 8);

    uint64_t res = 0;
    int ch;
    for (int i = 0; i < n_bytes; i++) {
        ch = hash_getc(file, hash);
        if (ch == EOF) {
            fprintf(stderr, "error: unexpected EOF in galaxy\n");
            exit(1);
        }

        res |= (ch << (i * 8));
    }

    return res;
}