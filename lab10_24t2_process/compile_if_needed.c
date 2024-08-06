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
        char *src_path = argv[i];
        char *bin_path = malloc(strlen(src_path) + 1);
        strcpy(bin_path, src_path);
        bin_path[strlen(src_path) - 2] = '\0';

        // check if neccessary to compile
        // get st of output file
        struct stat binary_st;
        if (stat(bin_path, &binary_st) == 0) {
            // check if the output file is newer than the input file
            struct stat src_st;
            if (stat(src_path, &src_st) == 0) {
                if (binary_st.st_mtime > src_st.st_mtime) {
                    printf("%s does not need compiling\n", src_path);
                    continue;
                }
            }
        }

        char *args[] = {DCC_PATH, src_path, "-o", bin_path, NULL};

        pid_t pid;
        int status;

        printf("running the command: \"%s %s -o %s\"\n", DCC_PATH, src_path, bin_path);
        if (posix_spawn(&pid, DCC_PATH, NULL, NULL, args, environ) == 0) {
            waitpid(pid, &status, 0);
        } else {
            perror("posix_spawn");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
