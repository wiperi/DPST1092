/*
$ dcc rm.c
$ ./a.out rm.c
$ ls -l rm.c
ls: cannot access 'rm.c': No such file or directory
$
*/

#include <stdio.h>
#include <unistd.h>

// remove the specified files
int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        if (unlink(argv[arg]) != 0) {
            perror(argv[arg]);  // prints why the unlink failed
            return 1;
        }
    }

    return 0;
}
