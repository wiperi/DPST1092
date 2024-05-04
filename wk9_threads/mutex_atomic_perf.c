//! An example demonstrating the performance discrepancy
//! between a Mutex guarding an unsigned int vs a single atomic_uint.
//!
//! Compile like:
//!   `clang -pthread -D <PERF_USE_NONE|PERF_USE_MUTEX|PERF_USE_ATOMIC> mutex_atomic_perf.c -o mutex_atomic_perf`
//!
//! It will then build the code using the preferred method of synchronisation.
//! Note that *no synchronisation* will almost certainly give an incorrect sum -- this is to be expected.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

// Make sure at-most one flag has been provided,
// otherwise we will have a compiler error
#ifdef PERF_USE_NONE
#ifdef PERF_USE_MUTEX
#error "only *one* option can be specified"
#endif // PERF_USE_MUTEX
#ifdef PERF_USE_ATOMIC
#error "only *one* option can be specified"
#endif // PERF_USE_ATOMIC
#endif // PERF_USE_NONE
#ifdef PERF_USE_MUTEX
#ifdef PERF_USE_ATOMIC
#error "only *one* option can be specified"
#endif // PERF_USE_ATOMIC
#endif // PERF_USE_MUTEX

// If no flag has been provided, default to NONE
#ifndef PERF_USE_NONE
#ifndef PERF_USE_MUTEX
#ifndef PERF_USE_ATOMIC
#define PERF_USE_NONE
#endif // PERF_USE_ATOMIC
#endif // PERF_USE_MUTEX
#endif // PERF_USE_NONE

// No synchronisation -- just a plain `unsigned int`
#ifdef PERF_USE_NONE
unsigned int count = 0;
#endif // PERF_USE_NONE

// Mutex synchronisation -- a lock and a plain `unsigned int`
//   that must be protected behind the lock
#ifdef PERF_USE_MUTEX
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
unsigned int count = 0;
#endif // PERF_USE_MUTEX

// Atomic synchronisation -- an `atomic_uint`
#ifdef PERF_USE_ATOMIC
atomic_uint count = 0;
#endif // PERF_USE_ATOMIC

void *thread(void *data) {
    unsigned long n_increments = *(unsigned long *)data;

#ifdef PERF_USE_NONE
    // If no synchronisation, just increment the count
    for (int i = 0; i < n_increments; i++) {
        count++;
    }
#endif // PERF_USE_NONE

#ifdef PERF_USE_MUTEX
    // If mutex synchronisation, acquire the
    // lock, increment the count, then release
    // the lock
    for (int i = 0; i < n_increments; i++) {
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    }
#endif // PERF_USE_MUTEX

#ifdef PERF_USE_ATOMIC
    // If atomic synchronisation, just
    // increment -- the synchronisation is
    // handled automagically for us!
    for (int i = 0; i < n_increments; i++) {
        count++;
    }
#endif // PERF_USE_ATOMIC

    return NULL;
}

int main(int argc, char *argv[]) {
    if (!argv[0] || !argv[1] || !argv[2]) {
        fprintf(stderr, "Usage: %s <n threads> <n increments per thread>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long n_threads = strtoul(argv[1], NULL, 0);
    unsigned long n_increments = strtoul(argv[2], NULL, 0);

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
    for (int i = 0; i < n_threads; i++) {
        pthread_create(&threads[i], NULL, thread, &n_increments);
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final result: %d\n", (int)count);
}
