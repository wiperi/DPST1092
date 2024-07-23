#include <stdio.h>
#include <stdlib.h>
#include <posix/unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    
    if (argc != 2) {
        printf("Usage: %s <command>\n", argv[0]);
    }
    
    // get command from argv
    char* command = argv[1];

    // get argument from stdio
    // excute command
    char arg[1024];

    while (fgets(arg, sizeof(arg), stdin) != NULL) {
        // execute command with argument
    }
}