// DPST1092 23T1 ... supp exam, question 6

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {

    assert(argc == 3);

    char *filename = argv[1];
    int line = atoi(argv[2]);

    FILE* src = fopen(filename, "r");
    FILE* dest = fopen("temp", "w");

    int ch;
    int n_line = 1;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), src) != NULL) {
        if (n_line != line) {
            fputs(buffer, dest);
        }
        n_line++;
    }

    fclose(src);
    fclose(dest);

    src = fopen(filename, "w");
    dest = fopen("temp", "r");

    while ((ch = fgetc(dest)) != EOF) {
        fputc(ch, src);
    }


    assert(line > 0);

    // ADD YOUR CODE HERE

    return 0;
}
