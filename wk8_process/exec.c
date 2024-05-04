/*
$ dcc exec.c
$ a.out
good-bye cruel world
$
*/

#include <stdio.h>
#include <unistd.h>

// simple example of program replacing itself with exec
int main(void) {
    char *echo_argv[] = {"/bin/echo","good-bye","cruel","world",NULL};
    execv("/bin/echo", echo_argv);

    // if we get here there has been an error
    perror("execv");
    return 1;
}
