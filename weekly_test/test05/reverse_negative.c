// Read numbers into an array until a negative number is entered
// then print the numbers in reverse order

#include <stdio.h>

#define ARRAY_LEN 1000
int numbers[ARRAY_LEN];

int main(void) {
    int i = 0;
    while (i < ARRAY_LEN) {
        int x;
        scanf("%d", &x);
        if (x < 0) {
            break;
        } else {
            numbers[i] = x;
        }
        i++;
    }

    while (i > 0) {
        i--;
        printf("%d\n", numbers[i]);
    }
}
