// Read 10 numbers into an array then print the numbers which are
// larger than the final number read.

#include <stdio.h>

#define ARRAY_LEN 10

int main(void) {
    int i, final_number;
    int numbers[ARRAY_LEN] = {0};

    i = 0;
    while (i < ARRAY_LEN) {
        scanf("%d", &numbers[i]);
        final_number = numbers[i];
        i++;
    }
    i = 0;
    while (i < ARRAY_LEN) {
        if (numbers[i] >= final_number) {
            printf("%d\n", numbers[i]);
        }
        i++;
    }
}

int simplified() {
    int i, final_number;
    int numbers[ARRAY_LEN] = {0};

    i = 0;
loop1:
    if (i >= ARRAY_LEN) goto loop1_end;

    // loop1 body
    scanf("%d", &numbers[i]);
    final_number = numbers[i];
    i++;
    // loop1 body
    goto loop1;
loop1_end:

loop2:
    if (i >= ARRAY_LEN) goto loop2_end;

    // loop2 body
    if (numbers[i] >= final_number) goto then1;
    goto else1;
then1:
    printf("%d\n", numbers[i]);
else1:

    i++;
    // loop2 body
    goto loop2;
loop2_end:
}