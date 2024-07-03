////////////////////////////////////////////////////////////////////////
// DPST1092 --- Assignment 2: `space', a simple file archiver
// 
//
// Written by Tianyang Chen (z5567323) on 3/July/2024.
//
// 2024-03-08   v1.1    Team DPST1092 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include "space.h"


// ADD ANY extra #defines HERE


// ADD YOUR FUNCTION PROTOTYPES (AND STRUCTS IF ANY) HERE

uint64_t little_endian_to_uint(void);

// print the files & directories stored in galaxy_pathname (subset 0)
//
// if long_listing is non-zero then file/directory permissions, formats & sizes
// are also printed (subset 0)

void list_galaxy(char *galaxy_pathname, int long_listing) {

    while (1) {
        check magic
        print magic
        check format
        check permissions
        get pathname len 
        check pathname
        get content len 
        check content
        check hash 
    }

}


// check the files & directories stored in galaxy_pathname (subset 1)
//
// prints the files & directories stored in galaxy_pathname with a message
// either, indicating the hash byte is correct, or indicating the hash byte
// is incorrect, what the incorrect value is and the correct value would be

void check_galaxy(char *galaxy_pathname) {

    while (1) {
        check magic
        print magic
        check format
        check permissions
        get pathname len 
        check pathname
        get content len 
        check content
        check hash 
    }
}


// extract the files/directories stored in galaxy_pathname (subset 1 & 3)

void extract_galaxy(char *galaxy_pathname) {

    check galaxy 

    get format 

    decode text and save to new file 
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

void create_galaxy(char *galaxy_pathname, int append, int format,
                   int n_pathnames, char *pathnames[n_pathnames]) {

    
    encode text 
    save to new file
}


// ADD YOUR EXTRA FUNCTIONS HERE
