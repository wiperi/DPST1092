// swap pairs of bits of a 64-bit value, using bitwise operators

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

_Atomic static int data = 0;

void costly_addition(int);

void *increment_and_sleep(void *arg)
{
    sleep(5);
    data++;
    return NULL;
}

int main(int argc, char **argv)
{
    printf("data: %d\n", data);

    costly_addition(atoi(argv[1]));

    printf("data: %d\n", data);

    return EXIT_SUCCESS;
}
