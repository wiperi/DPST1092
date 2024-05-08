//
// DPST1092 Lab 01 Exercise - no odd lines
// 
// Introduction:
// print only even lines
// 
// Reference
// 
// 
// Authors:
// Tianyang Chen (z5567323@unsw.edu.au)
// 
// Written: 5/8/2024
//
#include <stdio.h>

#define STRLIM 2048

int main(int argc, char* argv[], char* envp[]) {

    int n = 1;
    char str[STRLIM];

    while (fgets(str, STRLIM, stdin) != NULL) {

        if (n % 2 == 0) {
            // even line
            fputs(str, stdout);
        } else {
            // odd line
            ;
        }

        n++;
    }
}