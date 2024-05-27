// Read 10 numbers into an array
// swap any pair of numbers which are out of order
// then print the array

#include <stdio.h>

#define ARRAY_LEN 10

int main(void) {
    int i;
    int numbers[ARRAY_LEN] = { 0 };

    i = 0;
    while (i < ARRAY_LEN) {
        scanf("%d", &numbers[i]);
        i++;
    }

    i = 1;
    while (i < ARRAY_LEN) {
        int x = numbers[i];
        int y = numbers[i - 1];
        if (x < y) {
            numbers[i] = y;
            numbers[i - 1] = x;
        }
        i++;
    }

    i = 0;
    while (i < ARRAY_LEN) {
        printf("%d\n", numbers[i]);
        i++;
    }
}