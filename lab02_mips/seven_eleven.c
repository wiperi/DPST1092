// Read a number and print positive multiples of 7 or 11 < n

#include <stdio.h>

int main(void) {
    int number, i;

    printf("Enter a number: ");
    scanf("%d", &number);

    i = 1;
    while (i < number) {
        if (i % 7 == 0 || i % 11 == 0) {
            printf("%d\n", i);
        }
        i = i + 1;
    }

    return 0;
}

int simplified(void) {
    int number, i;

    printf("Enter a number: ");
    scanf("%d", &number);

    i = 1;
loop:
    if (i >= number) goto end;

    if (i % 7 == 0) goto print;
    if (i % 11 == 0) goto print;
    goto no_print;

print:
    printf("%d\n", i);
    
no_print:
    i++;
    goto loop;
end:
}
