// simple example of system

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // system passes string to a shell for evaluation
    // brittle and highly vulnerable to security exploits
    // system is suitable for quick debugging and throw-away programs only
    // run date --utc to print current UTC
    int exit_status = system("/bin/date --utc");
    printf("/bin/date exit status was %d\n", exit_status);
    return 0;
}
