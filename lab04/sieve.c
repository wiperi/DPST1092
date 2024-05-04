// Sieve of Eratosthenes
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
#include <stdio.h>
#include <string.h>

#define ARRAY_LEN 1000

char prime[ARRAY_LEN];

int simplified();

int main(void) {
    simplified();
    return 0;

    // Sets every element in the array to 1.
    // This has already been done for you
    // in the data segment of the provided MIPS code.
    memset(prime, 1, ARRAY_LEN);

    for (int i = 2; i < ARRAY_LEN; i++) {
        if (prime[i]) {
            printf("%d\n", i);
            for (int j = 2 * i; j < ARRAY_LEN; j += i) {
                prime[j] = 0;
            }
        }
    }

    return 0;
}

int simplified() {
    memset(prime, 1, ARRAY_LEN);

    int i = 2;
loop1_con:
    if (i < ARRAY_LEN) goto loop1_body;
    goto loop1_end;
loop1_body:

    if (prime[i]) goto if1_then;
    goto if1_else;
if1_then:
    printf("%d\n", i);

for1_init:
    int j = 2 * i;
for2_con:
    if (j < ARRAY_LEN) goto for2_body;
    goto for2_end;
for2_body:
    prime[j] = 0;

    j += i;
    goto for2_con;
for2_end:

if1_else:
if1_end:

    i++;
    goto loop1_con;
loop1_end:
}
