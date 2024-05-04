// print a 2d array

#include <stdio.h>

int numbers[3][5] = {{3, 9, 27, 81, 243}, {4, 16, 64, 256, 1024}, {5, 25, 125, 625, 3125}};

int main(void) {
    int i = 0;
    while (i < 3) {
        int j = 0;
        while (j < 5) {
            printf("%d", numbers[i][j]);
            printf("%c", ' ');
            j++;
        }
        printf("%c", '\n');
        i++;
    }
    return 0;
}

int simplified() {
    int t0 = 0;

loop1:
    if (t0 >= 3) goto loop1_end;
    // loop1 body
    int t1 = 0;

loop2:
    if (t1 >= 5) goto loop2_end;
    // loop2 body
    printf("%d", numbers[t0][t1]);
    printf("%c", ' ');
    t1++;
    goto loop2;
loop2_end:

    printf("%c", '\n');
    t0++;
    goto loop1;
loop1_end:
}
