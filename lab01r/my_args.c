//
// DPST1092 Lab 01 Exercise - my args
// 
// Introduction:
// print cmd args
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

int main(int argc, char* argv[], char* envp[]) {

    printf("There are %d arguments:\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("\tArgument %d is \"%s\"\n", i + 1, argv[i]);
    }
}