#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    time_t now = time(NULL);

    // open file
    for (int i = 1; i < argc; i++) {
        struct stat st;
        stat(argv[i], &st);

        if (st.st_atime > now || st.st_mtime > now) {
            printf("%s has a timestamp that is in the future\n", argv[i]);
        }
    }

    return 0;
}
