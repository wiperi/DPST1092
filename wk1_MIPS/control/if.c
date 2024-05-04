#include <stdio.h>

int main(void) {
    int i, n;
    if (i < 0) {
        n = n - i;
    } else {
        n = n + i;
    }
}

int simplified(int argc, char* argv[]) {
    int i, n;
    if (i >= 0) goto else1;
    n = n - i;
    goto end1;
else1:
    n = n + i;
end1:
}

int simplified_2() {
    int i, n;

    if (i < 0) goto then1;
    goto else1;
then1:
    n = n - i;
    goto end1;
else1:
    n = n + i;
    goto end1;
end1:
}
