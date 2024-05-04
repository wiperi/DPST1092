// simple example of use to popen to capture output

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // popen passes command to a shell for evaluation
    // brittle and highly-vulnerable to security exploits
    // popen is suitable for quick debugging and throw-away programs only
    //
    // tr a-z A-Z - passes stdin to stdout converting lower case to upper case

    FILE *p = popen("tr a-z A-Z", "w");
    if (p == NULL) {
        perror("");
        return 1;
    }

    fprintf(p, "plz date me - I know every SPIM system call\n");

    pclose(p); // returns command exit status
    return 0;
}
