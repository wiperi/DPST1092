#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {

    if (argc < 2) {
        printf("Usage: %s <word> <word> <word>...\n", argv[0]);
        return 0;
    }
    
    // get ${HOME}
    char *home = getenv("HOME");
    printf("%s\n", home);

    // open ${HOME}/.diary
    char diary_path[strlen(home) + strlen(".diary") + 2];
    sprintf(diary_path, "%s/%s", home, ".diary");

    FILE* diary = fopen(diary_path, "a");
    if(!diary) {
        perror(diary_path);
        exit(1);
    }

    // write to diary
    for (int i = 1; i < argc; i++) {
        if (i == argc - 1) {
            fprintf(diary, "%s\n", argv[i]);
        } else {
            fprintf(diary, "%s ", argv[i]);
        }
    }
}