#include <stdio.h>

int logic_and(int argc, char* argv[]) {
    int i, n;
    if (i < 0 && n >= 42) {
        n = n - i;
    } else {
        n = n + i;
    }
}

int and_simplified() {
    int i, n;
    if (i >= 0)
        goto else1;
    if (n < 42)
        goto else1;
    n = n - i;
    goto end1;
else1:
    n = n + i;
end1:
}

int logic_or() {
    int i, n;
    if (i < 0 || n >= 42) {
        n = n - i;
    } else {
        n = n + i;
    }
}

int or_simplified() {
    int i, n;
    if (i < 0)
        goto then1;
    if (n >= 42)
        goto then1;
    goto else1;
then1:
    n = n - i;
    goto end1;
else1:
    n = n + i;
end1:
}