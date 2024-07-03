#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {

    if (argc != 3) {
        printf("Usage: %s <file_path> <output_file_path>\n", argv[0]);
        return 1;
    }
    
    FILE* fa = fopen(argv[1], "r");
    if (!fa) {
        perror("fopen failed: ");
        exit(1);
    }

    FILE* fb = fopen(argv[2], "w");
    if (!fb) {
        perror("fopen failed: ");
        exit(1);
    }

    int cha;
    int chb;
    while (1) {
        cha = fgetc(fa);
        chb = fgetc(fb);

        if (cha == EOF) {
            printf("EOF on %s\n", argv[1]);
            return 0;
        }

        if (chb == EOF) {
            printf("EOF on %s\n", argv[2]);
            return 0;
        }

        if (cha != chb) {
            printf("Files differ at byte %d\n", ftell(fa));
            return 0;
        }
    }

    printf("Files are identical\n");

    fclose(fa);
    fclose(fb);

    return 0;
}