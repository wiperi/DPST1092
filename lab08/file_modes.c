#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void print_file_permissions(struct stat s) {
    // is dir ?
    if ((s.st_mode & S_IFDIR) == S_IFDIR) {
        printf("d");
    } else {
        printf("-");
    }

    // Owner Group Others
    if ((s.st_mode & S_IRUSR) == S_IRUSR)
        printf("r");
    else
        printf("-");
    if ((s.st_mode & S_IWUSR) == S_IWUSR)
        printf("w");
    else
        printf("-");
    if ((s.st_mode & S_IXUSR) == S_IXUSR)
        printf("x");
    else
        printf("-");
    if ((s.st_mode & S_IRGRP) == S_IRGRP)
        printf("r");
    else
        printf("-");
    if ((s.st_mode & S_IWGRP) == S_IWGRP)
        printf("w");
    else
        printf("-");
    if ((s.st_mode & S_IXGRP) == S_IXGRP)
        printf("x");
    else
        printf("-");
    if ((s.st_mode & S_IROTH) == S_IROTH)
        printf("r");
    else
        printf("-");
    if ((s.st_mode & S_IWOTH) == S_IWOTH)
        printf("w");
    else
        printf("-");
    if ((s.st_mode & S_IXOTH) == S_IXOTH)
        printf("x");
    else
        printf("-");
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file name> <file name>...\n", argv[0]);
        exit(1);
    }

    struct stat s;
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &s) != 0) {
            perror(argv[i]);
            exit(1);
        }
        print_file_permissions(s);
        printf(" %s\n", argv[i]);
    }

}