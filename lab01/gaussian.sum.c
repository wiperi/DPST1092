// A simple C program that calculates the Gaussian sum between two numbers
// Written 12/2/2022
// by Dylan Brotherston (d.brotherston@unsw.edu.au)

#include <stdio.h>

int main(void) {
    int number1, number2;

    printf("Enter first number: ");
    scanf("%d", &number1);

    printf("Enter second number: ");
    scanf("%d", &number2);

    int gaussian_sum = ((number2 - number1 + 1) * (number1 + number2)) / 2;

    printf("The sum of all numbers between %d and %d (inclusive) is: %d\n", number1, number2, gaussian_sum);

    return 0;
}