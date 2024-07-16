// Reads 10 numbers into an array, bubblesorts them
// and then prints the 10 numbers
// then print them

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

    int swapped = 1;
    while (swapped) {
        swapped = 0;
        i = 1;
        while (i < ARRAY_LEN) {
            int x = numbers[i];
            int y = numbers[i - 1];
            if (x < y) {
                numbers[i] = y;
                numbers[i - 1] = x;
                swapped = 1;
            }
            i++;
        }
    }

    i = 0;
    while (i < ARRAY_LEN) {
        printf("%d\n", numbers[i]);
        i++;
    }
}