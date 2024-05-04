// demonstrate implementaion of pointers by an address

#include <stdio.h>

int answer = 42;

int main(void) {
    int i;
    int *p;

    p = &answer;
    i = *p;
    // prints 42
    printf("%d\n", i); 
    *p = 27;
    // prints 27
    printf("%d\n", answer); 

    return 0;
}
