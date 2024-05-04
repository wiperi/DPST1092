#include <stdio.h>

int main(int argc, char* argv[]) {

    int i = 0;
    int n = 0;
loop:
    if (i >= 5)
        goto end;
    n = n + i;
    i++;
    goto loop;
end:
}