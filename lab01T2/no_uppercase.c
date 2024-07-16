//
// DPST1092 Lab 01 Exercise - no uppercase
//
// Introduction:
// convert all uppercase letters to lowercase, other remain still.
//
// Reference
//
//
// Authors:
// Tianyang Chen (z5567323@unsw.edu.au)
//
// Written: 8/5/2024
//
#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[], char* envp[]) {

    int ch = 0;

    while ((ch = getchar()) != EOF) {

        if (isupper(ch)) {
            ch = tolower(ch);
        }

        putchar(ch);
    }
}