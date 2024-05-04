/*
$ dcc fork.c
$ a.out
I am the parent because fork() returned 2884551.
I am the child because fork() returned 0.
$
*/

#include <stdio.h>
#include <unistd.h>

int main(void) {

    // fork creates 2 identical copies of program
    // only return value is different

    pid_t pid = fork();

    if (pid == -1) {
         perror("fork");  // print why the fork failed
    } else if (pid == 0) {
        printf("I am the child because fork() returned %d.\n", pid);
    } else {
        printf("I am the parent because fork() returned %d.\n", pid);
    }

    return 0;
}
