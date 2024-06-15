//  Reads a line from stdin and an integer n,
//  and then prints the character in the nth-position

#include <stdio.h>

// line of input stored here
#define LINE_LEN 256
char line[LINE_LEN];

int main(void) {

    printf("Enter a line of input: ");
    fgets(line, LINE_LEN, stdin);

    printf("Enter a position: ");
    int n;
    scanf("%d", &n);

    printf("Character is: ");
    putchar(line[n]);
    putchar('\n');

    return 0;
}
