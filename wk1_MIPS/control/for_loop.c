#include <stdio.h>

int main(void) {
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
        sum += i * i;
    }
    printf("%d\n", sum);
    return 0;
}

#define UPPER_BOUND 100

int simplified(void) {
    int sum = 0;
loop_i_to_100__init:;
    int i = 0;
loop_i_to_100__cond:
    if (i > UPPER_BOUND)
        goto loop_i_to_100__end;
loop_i_to_100__body:
    sum += i * i;
loop_i_to_100__step:
    i++;
    goto loop_i_to_100__cond;
loop_i_to_100__end:
    printf("%d", sum);
    putchar('\n');
    return 0;
}