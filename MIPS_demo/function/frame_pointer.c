// example of function where frame pointer useful
// because stack grows during function execution

#include <stdio.h>
#include <stdlib.h>

void f(int a) {
    int length;
    scanf("%d", &length);

    int* array = (int*) malloc(length * sizeof(int));
    // ... more code ...
    free(array);
}