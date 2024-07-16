// read a number n and print the integers 1..n one per line

#include <stdio.h>

int main(void) {
    int number, i;

    printf("Enter a number: ");
    scanf("%d", &number);

    i = 1;
    while (i <= number) {
        printf("%d\n", i);
        i = i + 1;
    }

    return 0;
}

int simplified() {
    int number;
    int i = 1;
loop:
    if (i > number)
        goto end;
    printf("%d", i);
    printf("\n");
    i++;
    goto loop;
end:
    return;
}