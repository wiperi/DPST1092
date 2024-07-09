// compile .c files specified as command line arguments
//
// if my_program.c and other_program.c is speicified as an argument then the follow two command will be executed:
// /usr/local/bin/dcc my_program.c -o my_program
// /usr/local/bin/dcc other_program.c -o other_program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <file1.c> <file2.c> <file3.c>...\n", argv[0]);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char *file = argv[i];
        char *output = malloc(strlen(file) + 1);
        strcpy(output, file);
        output[strlen(file) - 2] = '\0';

        char *args[] = {DCC_PATH, file, "-o", output, NULL};

        pid_t pid;
        int status;

        if (posix_spawn(&pid, DCC_PATH, NULL, NULL, args, environ) == 0) {
            waitpid(pid, &status, 0);
        } else {
            perror("posix_spawn");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
