/*

Simple example demonstrating safe access to a global variable from
threads, using atomics

    $ gcc -O3 -pthread bank_account_atomic.c -o bank_account_atomic
    $ ./bank_account_atomic
    Andrew's bank account has $200000
    $

*/

#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

atomic_int bank_account = 0;

// add $1 to Andrew's bank account 100,000 times
void *add_100000(void *argument) {
    for (int i = 0; i < 100000; i++) {
        // NOTE: This *cannot* be `bank_account = bank_account + 1`,
        // as that will not be atomic!
        // However, `bank_account++` would be okay
        // and,     `atomic_fetch_add(&bank_account, 1)` would also be okay
        bank_account += 1;
    }

    return NULL;
}

int main(void) {
    // create two threads performing  the same task

    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, add_100000, NULL);

    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, add_100000, NULL);

    // wait for the 2 threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    // will always be $200000
    printf("Andrew's bank account has $%d\n", bank_account);
    return 0;
}
