// compile .c files specified as command line arguments
//
// if my_program.c and other_program.c is speicified as an argument then the follow two command will be executed:
// /usr/local/bin/dcc my_program.c -o my_program
// /usr/local/bin/dcc other_program.c -o other_program

#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// #define DCC_PATH "/usr/local/bin/dcc"
#define DCC_PATH "/usr/bin/gcc"

extern char** environ;

int main(int argc, char** argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_name>...", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        // build args
        char file_name[1024];
        strncat(file_name, argv[i], strlen(argv[i]) - 2);
        char* arg[] = {DCC_PATH, argv[i], "-o", file_name};

        // create process
        pid_t pid;
        if (posix_spawn(&pid, DCC_PATH, NULL, NULL, arg, environ) != 0) {
            perror("posix_spawn error");
            exit(1);
        }
    }

    int st;
    while (waitpid(-1, &st, 0) > 0) {
        continue;
    }

    return EXIT_SUCCESS;
}
