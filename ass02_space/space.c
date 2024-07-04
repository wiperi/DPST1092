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

#define DEBUG_MODE 0
#define DEBUG_MESSAGE_OFFSET_STRING 20
#define DEBUG_MESSAGE_OFFSET_OTHER 10

// ADD YOUR FUNCTION PROTOTYPES (AND STRUCTS IF ANY) HERE

uint8_t check_galaxy_mode = 0;
# define SILENCE 0x1
# define LIST_STARS 0x2
# define LIST_STARS_VERBOSE 0x4

// macro to decode mode
# define CHECK_GALAXY_MODE(M) (check_galaxy_mode & M)

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

    check_galaxy_mode |= SILENCE;
    if (long_listing) {
        check_galaxy_mode |= LIST_STARS_VERBOSE;
    } else {
        check_galaxy_mode |= LIST_STARS;
    }
    check_galaxy(galaxy_pathname);
    check_galaxy_mode = 0;

}

// check the files & directories stored in galaxy_pathname (subset 1)
//
// prints the files & directories stored in galaxy_pathname with a message
// either, indicating the hash byte is correct, or indicating the hash byte
// is incorrect, what the incorrect value is and the correct value would be

void check_galaxy(char* galaxy_pathname) {

    /**
     * pseudo:
     * 
     * open file
     * 
     * check if file end
     * check magic
     * check format
     * check permissions
     * read path len
     * check path name
     * read content len
     * check content
     * check hash
     */

    FILE* file = fopen(galaxy_pathname, "r");
    if (file == NULL) {
        fprintf(stderr, "%s: No such file or directory", galaxy_pathname);
        exit(1);
    }

    int ch;

    while (1) {
        // check if file ends
        ch = fgetc(file);
        fseek(file, -1, SEEK_CUR);
        if (ch == EOF) {
            return;
        }

        uint8_t hash = 0;

        // check magic
        ch = hash_getc(file, &hash);
        if (ch != 'c') {
            fprintf(stderr,
                    "error: incorrect first star byte: 0x%x should be 0x63\n", ch);
            exit(1);
        }
        if (DEBUG_MODE) printf("%-*s %*c\n", DEBUG_MESSAGE_OFFSET_STRING, "magic:", DEBUG_MESSAGE_OFFSET_OTHER, ch);

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
        char star_format = ch;
        if (DEBUG_MODE) printf("%-*s %*c\n", DEBUG_MESSAGE_OFFSET_STRING, "star format:", DEBUG_MESSAGE_OFFSET_OTHER, ch);

        // check permissions
        int permissions_invalid = 0;
        char permissions[11];
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
                    case 'x':
                        break;
                    default:
                        permissions_invalid = 1;
                        break;
                }
            }
        }
        permissions[10] = '\0';
        if (permissions_invalid) {
            fprintf(stderr, "error: invalid permission string %s\n", permissions);
            exit(1);
        }
        if (DEBUG_MODE) printf("%-*s %*s\n", DEBUG_MESSAGE_OFFSET_STRING, "permisson:", DEBUG_MESSAGE_OFFSET_OTHER, permissions);

        // check pathlen
        uint64_t pathlen = little_endian_to_uint(file, 2, &hash);
        if (DEBUG_MODE) printf("%-*s %*lx\n", DEBUG_MESSAGE_OFFSET_STRING, "pathlen:", DEBUG_MESSAGE_OFFSET_OTHER, pathlen);

        // read path name
        char path_name[pathlen + 1];
        for (int i = 0; i < pathlen; i++) {
            ch = hash_getc(file, &hash);

            path_name[i] = ch;
        }
        path_name[pathlen] = '\0';
        if (DEBUG_MODE) printf("%-*s %*s\n", DEBUG_MESSAGE_OFFSET_STRING, "path name:", DEBUG_MESSAGE_OFFSET_OTHER, path_name);

        // read content len
        uint64_t content_len = little_endian_to_uint(file, 6, &hash);
        if (DEBUG_MODE) printf("%-*s %*lx\n", DEBUG_MESSAGE_OFFSET_STRING, "content len:", DEBUG_MESSAGE_OFFSET_OTHER, content_len);

        // check content
        char content[content_len + 1];
        for (int i = 0; i < content_len; i++) {
            ch = hash_getc(file, &hash);

            content[i] = ch;
        }
        content[content_len] = '\0';
        if (DEBUG_MODE) printf("%-*s %*s\n", DEBUG_MESSAGE_OFFSET_STRING, "content:", DEBUG_MESSAGE_OFFSET_OTHER, content);

        // check hash
        int hash_byte = fgetc(file);
        if (hash_byte == EOF) {
            fprintf(stderr, "error: unexpected EOF in galaxy\n");
            exit(1);
        }

        // print hash comparision ressult
        if (CHECK_GALAXY_MODE(SILENCE)) {
            if (hash_byte == hash) {
                ;
            } else {
                fprintf(stderr, "%s - incorrect hash 0x%x should be 0x%x\n", path_name, hash, hash_byte);
                exit(1);
            }
        } else {
            if (hash_byte == hash) {
                printf("%s - correct hash\n", path_name);
            } else {
                printf("%s - incorrect hash 0x%x should be 0x%x\n", path_name, hash, hash_byte);
            }
        }

        // list stars
        if (CHECK_GALAXY_MODE(LIST_STARS_VERBOSE)) {
            printf("%10s %2c %6ld  %s\n", permissions, star_format, content_len, path_name);
        } else if (CHECK_GALAXY_MODE(LIST_STARS)) {
            printf("%s\n", path_name);
        }
    }
}

// extract the files/directories stored in galaxy_pathname (subset 1 & 3)

void extract_galaxy(char* galaxy_pathname) {

    /**
     * pseudo:
     * 
     * check galaxy
     */
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
    if (ch == EOF) {
        fprintf(stderr, "error: unexpected EOF in galaxy\n");
        exit(1);
    }
    *hash = galaxy_hash(*hash, ch);
    return ch;
}

uint64_t little_endian_to_uint(FILE* file, int n_bytes, uint8_t* hash) {

    assert(n_bytes <= 8);

    uint64_t res = 0;
    int ch;
    for (int i = 0; i < n_bytes; i++) {
        ch = hash_getc(file, hash);

        res |= ((uint64_t) ch << (i * 8));
    }

    return res;
}