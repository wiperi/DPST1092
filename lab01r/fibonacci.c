//
// DPST1092 Lab 02 Exercise - fibonacci
//
// Introduction:
// recirsive calculate fibonacci
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
#include <stdlib.h>

#define SERIES_MAX 30

int fibonacci(int n) {

    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {

    int n;
    while (scanf("%d", &n) != EOF) {

        if (n >= 0 && n <= SERIES_MAX) {
            printf("%d\n", fibonacci(n));
        } else {
            printf("Invalid input. Please enter a number between 0..%d.\n", SERIES_MAX);
        }
    }
    return EXIT_SUCCESS;
}
