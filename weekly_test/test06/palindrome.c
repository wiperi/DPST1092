// Reads a line and prints whether it is a palindrome or not
#include <stdio.h>

#define LINE_LEN 256

// line of input stored here
char line[LINE_LEN];

int main(void) {
    printf("Enter a line of input: ");
    fgets(line, LINE_LEN, stdin);

    int i = 0;
    while (line[i] != 0) {
        i++;
    }
    int j = 0;
    int k = i - 2;
    while (j < k) {
        if (line[j] != line[k]) {
            printf("not palindrome\n");
            return 0;
        }
        j++;
        k--;
    }
    printf("palindrome\n");
    return 0;
}
