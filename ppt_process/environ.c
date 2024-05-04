// print all environment variables
#include <stdio.h>

int main(void) {
    // print all environment variables
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n\n", environ[i]);
    }
}