// Read three numbers `start`, `stop`, `step`
// Print the integers bwtween `start` and `stop` moving in increments of size `step`

#include <stdio.h>


int main(void) {

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
