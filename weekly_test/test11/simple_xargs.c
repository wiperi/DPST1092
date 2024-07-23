#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

extern char** environ;

int main(int argc, char *argv[]) {
    char *command = argv[1];
    char line[MAX_LINE_LENGTH];
    char *args[3];
    pid_t pid;

    args[0] = command;
    args[2] = NULL;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        *(strchr(line, '\n')) = '\0';
        args[1] = line;

        posix_spawn(&pid, command, NULL, NULL, args, environ);
        waitpid(pid, NULL, 0);
    }

    return 0;
}