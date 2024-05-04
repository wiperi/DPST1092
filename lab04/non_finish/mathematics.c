void seed_rand(unsigned int);
int  rand(unsigned int);
int  add_rand(int);
int  sub_rand(int);
int  seq_rand(int);

#include <stdio.h>

int main(void)
{
    int random_seed;
    printf("Enter a random seed: ");
    scanf("%d", &random_seed);

    seed_rand(random_seed);

    int value = rand(100);
    value = add_rand(value);
    value = sub_rand(value);
    value = seq_rand(value);

    printf("The random result is: %d\n", value);

    return 0;
}

int add_rand(int value)
{
    return value + rand(0xFFFF);
}

int sub_rand(int value)
{
    return value - rand(value);
}

int seq_rand(int value)
{
    int limit = rand(100);
    for (int i = 0; i < limit; i++)
    {
        value = add_rand(value);
    }
    return value;
}

//////////////////////// PROVIDED CODE ////////////////////////

#define OFFLINE_SEED 0x7F10FB5B

int random_seed;

// seed the random number generator
// with the given seed value
void seed_rand(unsigned int seed)
{
    const unsigned int offline_seed = OFFLINE_SEED;
    random_seed = seed ^ offline_seed;
}

// return a random number between
// 0 and (n - 1) inclusive.
// *n must be greater than 0*
int rand(unsigned int n)
{
    unsigned int rand = random_seed;
    rand *= 0x5bd1e995;
    rand += 12345;
    random_seed = rand;
    return rand % n;
}