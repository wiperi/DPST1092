
/*
$ dcc chmod.c
$ ls -l chmod.c
-rw-r--r-- 1 z5555555 z5555555 746 Nov  4 08:20 chmod.c
$ ./a.out 600 chmod.c
$ ls -l chmod.c
-rw------- 1 z5555555 z5555555 787 Nov  4 08:22 chmod.c
$ ./a.out 755 chmod.c
chmod.c 755
$ ls -l chmod.c
-rwxr-xr-x 1 z5555555 z5555555 787 Nov  4 08:22 chmod.c
$
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// change permissions of the specified files
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <mode> <files>\n", argv[0]);
        return 1;
    }

    char *end;
    // first argument is mode in octal
    __mode_t mode = strtol(argv[1], &end, 8);

    // check first argument was a valid octal number
    if (argv[1][0] == '\0' || end[0] != '\0') {
        fprintf(stderr, "%s: invalid mode: %s\n", argv[0], argv[1]);
        return 1;
    }

    for (int arg = 2; arg < argc; arg++) {
        if (chmod(argv[arg], mode) != 0) {
            perror(argv[arg]);  // prints why the chmod failed
            return 1;
        }
    }

    return 0;
}
