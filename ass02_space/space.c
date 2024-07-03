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


// print the files & directories stored in galaxy_pathname (subset 0)
//
// if long_listing is non-zero then file/directory permissions, formats & sizes
// are also printed (subset 0)

void list_galaxy(char *galaxy_pathname, int long_listing) {

    // REPLACE THIS CODE WITH YOUR CODE

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

void check_galaxy(char *galaxy_pathname) {

    // REPLACE THIS PRINTF WITH YOUR CODE

    printf("check_galaxy called to check galaxy: '%s'\n", galaxy_pathname);
}


// extract the files/directories stored in galaxy_pathname (subset 1 & 3)

void extract_galaxy(char *galaxy_pathname) {

    // REPLACE THIS PRINTF WITH YOUR CODE

    printf("extract_galaxy called to extract galaxy: '%s'\n", galaxy_pathname);
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
