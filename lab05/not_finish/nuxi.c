#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>


int main(int argc, char* argv[]) {

    int order[26];
    order['U' - 'A'] = 0;
    order['N' - 'A'] = 1;
    order['I' - 'A'] = 2;
    order['X' - 'A'] = 3;

    // read two 32 bit nubmer
    int a = 1481199189;
    int b = -2023406815;

    unsigned char *m = (unsigned char*) &a;
    unsigned char *n = "PSMI";

    char res[5];
    for (int i = 0; i < 4; i++) {
        printf("%c\n", m[i]);
        printf("%d\n", order[m[i] - 'A']);
        res[i] = n[order[m[i] - 'A']];
    }
    res[4] = '\0';
    
    printf("%s\n", res);
}