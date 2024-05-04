//! A small program that demonstrates lifetime issues
//! with respect to differing threads
//!
//! When compiled with `dcc`:
//! $ dcc -pthread thread_data_broken.c -o thread_data_broken
//! $ ./thread_data_broken
//! Hello there! Please patiently wait for your number!
//! The number is 0x6c6c6548!
//!
//! Note that the 0x6c6c6548 value can easily change between
//! compilers, platforms, or even individual executions.
//! In this case, 0x6c6c6548 is the four ASCII bytes:
//! 'l', 'l', 'e', 'H' -- the first four letters of "Hello there..."
//! in little-endian byte ordering
//!
//! Curiously, the correct answer will occasionally appear:
//! $ ./thread_data_broken
//! Hello there! Please patiently wait for your number!
//! The number is 0x42!
//!

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *my_thread(void *data) {
    int number = *(int *)data;

    sleep(1);
    // should print 0x42, probably won't
    printf("The number is 0x%x!\n", number);

    return NULL;
}

pthread_t create_thread(void) {
    int super_special_number = 0x42;

    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, &super_special_number);
    // super_special_number is destroyed when create_thread returns
    // but the thread just created may still be running and access it
    return thread_handle;
}

/// This function is entirely innocent but calling it below
/// (probably) makes the bug in create_thread obvious by changing stack memory
void say_hello(void) {
    char greeting[] = "Hello there! Please patiently wait for your number!\n";
    printf("%s", greeting);
}

int main(void) {
    pthread_t thread_handle = create_thread();

    say_hello();

    pthread_join(thread_handle, NULL);
}
