#include <stdio.h>

#define ARRAY_LEN 10

int numbers[ARRAY_LEN];

int main(void) {
    int x, i, n_seen;

    n_seen = 0;
    while (n_seen < ARRAY_LEN) {
        printf("Enter a number: ");
        scanf("%d", &x);

        i = 0;
        while (i < n_seen) {
            if (x == numbers[i]) {
                break;
            }
            i++;
        }

        if (i == n_seen) {
            numbers[n_seen] = x;
            n_seen++;
        }
    }
    printf("10th different number was %d\n", x);

    return 0;
}
