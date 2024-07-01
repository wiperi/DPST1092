#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename1> <filename2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        struct stat state;
        if (stat(argv[i], &state) == -1) {
            perror("Error");
            continue;
        }

        printf("%s: %ld bytes\n", argv[i], state.st_size);
    }

    return 0;
}