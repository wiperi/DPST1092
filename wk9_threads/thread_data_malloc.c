//! A potential solution to the issue in thread_data_broken.c
//!
//! This program uses a heap allocation to make sure that
//! the memory will not be deallocated before the thread
//! has a chance to read it.
//!
//! This in turn means that the thread is responsible for freeing
//! the passed-in data.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *my_thread(void *data) {
    int number = *(int *)data;

    sleep(1);
    printf("The number is 0x%x!\n", number);

    free(data);
    return NULL;
}

pthread_t function_creates_thread(void) {
    int *super_special_number = malloc(sizeof(int));
    *super_special_number = 0x42;

    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, super_special_number);

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
