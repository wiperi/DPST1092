#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_FILES 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <list_of_files>\n", argv[0]);
        return 1;
    }

    ino_t seen_files[MAX_FILES];
    int seen_count = 0;

    for (int i = 1; i < argc; i++) {
        struct stat file_stat;

        if (stat(argv[i], &file_stat) != 0) {
            perror("stat");
            continue;
        }

        int found = 0;
        for (int j = 0; j < seen_count; j++) {
            if (seen_files[j] == file_stat.st_ino) {
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("%s\n", argv[i]);
            if (seen_count < MAX_FILES) {
                seen_files[seen_count++] = file_stat.st_ino;
            } else {
                fprintf(stderr, "Too many files.\n");
                break;
            }
        }
    }

    return 0;
}