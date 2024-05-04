/**
 * Introduction:
 *
 * Create a thread and print hello.
 */
#include <pthread.h>
#include <stdio.h>

void* thread_func(void*) {
    printf("Thread: Hello father.\n");

    return NULL;
}

int main(int argc, char* argv[], char* envp[]) {

    // create a thread
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_func, NULL);

    return 0;
}