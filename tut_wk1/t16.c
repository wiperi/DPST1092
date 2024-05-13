#include <stdio.h>
#define N 10

int main(void) {

    my_main();
    return 0;

    int a[] = {4, 3, 9, -8, 5, -4, 3, 1, 0, 4};
    int sum = 0;
    int i;
    for (i = 0; i < N; i++) {
        if (a[i] == 0) break;
        if (a[i] < 0) continue;
        sum += a[i];
    }
    printf("The sum is %d\n", sum);
    return 0;
}

int my_main() {
    int a[] = {4, 3, 9, -8, 5, -4, 3, 1, 0, 4};
    int sum = 0;
    int i;
    for (i = 0; i < N; i++) {
        if (a[i] == 0) {
            printf("The sum is %d\n", sum);
            return 0;
        }
        if (a[i] >= 0) {
            sum += a[i];
        }
    }
}