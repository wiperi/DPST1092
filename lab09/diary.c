#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string> <string>.", argv[0]);
        exit(1);
    }

    // get the path of diary
    char* path = getenv("HOME");
    path = strcat(path, "/.diary");

    // printf("%s\n", path);    

    FILE* diary = fopen(path, "a");
    for (int i = 1; i < argc; i++) {
        fprintf(diary, "%s ", argv[i]);
    }
    fprintf(diary, "\n");
}