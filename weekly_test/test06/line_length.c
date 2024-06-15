// Reads a line and print its length
#include <stdio.h>

// line of input stored here
#define LINE_LEN 256
char line[LINE_LEN];

int main(void) {
    printf("Enter a line of input: ");
    fgets(line, LINE_LEN, stdin);

    int i = 0;
    while (line[i] != 0) {
        i++;
    }

    printf("Line length: ");
    printf("%d", i);

    putchar('\n');
    return 0;
}
