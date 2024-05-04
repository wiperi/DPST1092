// Read 10 numbers into an array
// print 0 if they are in non-decreasing order
// print 1 otherwise

#include <stdio.h>

#define ARRAY_LEN 10

int main(void) {
    int i;
    int numbers[ARRAY_LEN] = {0};

    i = 0;
    while (i < ARRAY_LEN) {
        scanf("%d", &numbers[i]);
        i++;
    }

    int swapped = 0;
    i = 1;
    while (i < ARRAY_LEN) {
        int x = numbers[i];
        int y = numbers[i - 1];
        if (x < y) {
            swapped = 1;
        }
        i++;
    }

    printf("%d\n", swapped);
}