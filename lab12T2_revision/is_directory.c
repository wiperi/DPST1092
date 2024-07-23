#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char* argv[], char* envp[]) {

    struct stat st;
    if (stat(argv[1], &st) < 0) {
        printf("%d\n", 0);
        exit(0);
    }

    if (S_ISDIR(st.st_mode)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }
}