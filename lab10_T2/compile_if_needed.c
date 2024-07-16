#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <file1.c> <file2.c> <file3.c>...\n", argv[0]);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char *path = argv[i];
        char *binary_file = malloc(strlen(path) + 1);
        strcpy(binary_file, path);
        binary_file[strlen(path) - 2] = '\0';

        // check if neccessary to compile
        // get st of output file
        struct stat binary_st;
        if (stat(binary_file, &binary_st) == 0) {
            // check if the output file is newer than the input file
            struct stat src_st;
            if (stat(path, &src_st) == 0) {
                if (binary_st.st_mtime > src_st.st_mtime) {
                    continue;
                }
            }
        }

        char *args[] = {DCC_PATH, path, "-o", binary_file, NULL};

        pid_t pid;
        int status;

        printf("running the command: \"%s %s -o %s\"\n", DCC_PATH, path, binary_file);
        if (posix_spawn(&pid, DCC_PATH, NULL, NULL, args, environ) == 0) {
            waitpid(pid, &status, 0);
        } else {
            perror("posix_spawn");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
