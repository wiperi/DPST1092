#include <stdint.h>
#include <stdio.h>

char m[4], n[4];

void int_to_char_arr(uint32_t a, char* tar) {

    int mask = 0xff;

    char ch;
    int j = 0;
    for (int i = 0; i < 4; i++) {
        ch = mask & (a >> (i * 8));
        tar[j] = ch;

        j++;
    }

    printf("%s\n", tar);
}

void nuxi(char* m, char* n) {

    // tar[4] = "UNIX"

    // int i, j;

    // j = 0;
    // while (n[j] != tar[i]) {
    //     j++;
    // }
    // i++;
    // res.add n[j]

    char res[5] = {0};
    char tar[] = "UNIX";

    int tar_i = 0, i = 0;

    while (1) {

        if (tar_i >= 4 || i >= 4) {
            res[4] = '\0';
            printf("%s\n", res);
            return;
        }

        i = 0;

        while (m[i] != tar[tar_i]) {
            i++;
        }

        res[tar_i] = n[i];

        tar_i++;
    }
}

int main(int argc, char* argv[], char* envp[]) {
    int_to_char_arr(1481199189, m);
    int_to_char_arr(-2023406815, n);
    
    int a = 1481199189;
    int b = -2023406815;
    nuxi(&a, &b);
}