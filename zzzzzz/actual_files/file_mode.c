#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

// Function to print the file permissions in the format used by ls -l
void print_permissions(mode_t mode) {
    printf("%c", (S_ISDIR(mode)) ? 'd' : '-');
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pathname>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        struct stat file_stat;
        if (stat(argv[i], &file_stat) == -1) {
            perror(argv[i]);
            continue;
        }

        print_permissions(file_stat.st_mode);
        printf(" %s\n", argv[i]);
    }

    return 0;
}
