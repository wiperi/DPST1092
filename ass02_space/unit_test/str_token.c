#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    

    char* res = strtok("first/second/third", "/");

    printf("%s\n", res);
}