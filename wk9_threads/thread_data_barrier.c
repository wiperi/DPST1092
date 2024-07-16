//! A potential solution to the issue in thread_data_broken.c
//!
//! This program does not need an allocation in order to fix
//! the previous lifetime issue. Instead it makes sure the thread
//! has a chance to read the memory (and copy it into its own stack)
//! before it is deallocated, by using a barrier.
//!
//! The barrier is initialised with a value of 2:
//! - One for the caller thread, so it doesn't deallocate the memory immediately
//! - One for the called thread, so it can signal when it has copied the memory
//!
//! Performance in execution speed is incredibly similar to malloc-version,
//! but does not rely on additional allocation, which is an occasional
//! real-world constraint.
//!
//! NOTE: `dcc` tends to not like this example code
//! try running with `clang` or `gcc` instead.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct thread_data {
    pthread_barrier_t* barrier;
    int number;
};

void* my_thread(void* data) {
    struct thread_data* thread_data = (struct thread_data*)data;
    int number = thread_data->number;
    pthread_barrier_wait(thread_data->barrier);

    sleep(1);
    printf("The number is 0x%x!\n", number);

    return NULL;
}

pthread_t function_creates_thread(void) {

    // the barrier is initialized with a count of 2, meaning it will make sure
    // that both the main thread and the new thread created must reach the
    // barrier before either of them can proceed.
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, 2);

    struct thread_data data = {
        .barrier = &barrier,
        .number = 0x42,
    };

    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, &data);

    pthread_barrier_wait(&barrier);

    return thread_handle;
}

void function_says_hello(void) {
    char greeting[] = "Hello there! Please patiently wait for your number!\n";
    printf("%s", greeting);
}

int main(void) {
    pthread_t thread_handle = function_creates_thread();

    function_says_hello();

    pthread_join(thread_handle, NULL);
}
