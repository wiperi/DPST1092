#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file name> <nubmer> <nubmer>\n", argv[0]);
        exit(1);
    }

    char* file_name = argv[1];
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    // create the file
    FILE* new_file = fopen(file_name, "w");
    // write in nubmers
    for (int i = start; i <= end; i++) {
        fprintf(new_file, "%d\n", i);
    }
    fclose(new_file);
}