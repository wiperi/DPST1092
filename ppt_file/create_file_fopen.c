// create file "hello.txt" containing 1 line: Hello, Zac!

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *output_stream = fopen("hello.txt", "w");
    if (output_stream == NULL) {
        perror("hello.txt");
        return 1;
    }

    fprintf(output_stream, "Hello, Zac!\n");

    // fclose will flush data to file, best to close file ASAP
    // optional here as fclose occurs automatically on exit
    fclose(output_stream);

    return 0;
}
