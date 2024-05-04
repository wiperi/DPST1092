// Read three numbers `start`, `stop`, `step`
// Print the integers bwtween `start` and `stop` moving in increments of size `step`

#include <stdio.h>

int simplified();

int main(void) {

    simplified();

    int start, stop, step;

    printf("Enter the starting number: ");
    scanf("%d", &start);

    printf("Enter the stopping number: ");
    scanf("%d", &stop);

    printf("Enter the step size: ");
    scanf("%d", &step);

    if (stop < start) {
        if (step < 0) {
            for (int i = start; i >= stop; i += step) {
                printf("%d\n", i);
            }
        }
    }

    if (stop > start) {
        if (step > 0) {
            for (int i = start; i <= stop; i += step) {
                printf("%d\n", i);
            }
        }
    }

    return 0;
}

int simplified() {
    int start, stop, step, i;

    printf("Enter the starting number: ");
    scanf("%d", &start);

    printf("Enter the stopping number: ");
    scanf("%d", &stop);

    printf("Enter the step size: ");
    scanf("%d", &step);

    // part 1
    if (stop >= start) goto skip_loop1;
    if (step >= 0) goto skip_loop1;
    // for loop
    i = start;
loop1:
    if (i > stop) goto loop1_end;
    printf("%d\n", i);
    i += step;
    goto loop1;
loop1_end:
    // end of for loop
skip_loop1:

    // part 2
    if (stop <= start) goto skip_loop2;
    if (step <= 0) goto skip_loop2;
    // for loop
    i = start;
loop2:
    if (i > stop) goto loop2_end;
    printf("%d\n", i);
    i += step;
    goto loop2;
loop2_end:
    // end of for loop
skip_loop2:
}
