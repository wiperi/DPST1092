/**
 * Introduction:
 *
 * Create a thread and print hello.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void* arg) {

    printf("Thread: Father told me: %s\n", (char*) arg);

    // return a value
    int* ret = (int*) malloc(sizeof(int));
    *ret = 666;
    return (void*) ret;
}

int main(int argc, char* argv[], char* envp[]) {

    // create a thread
    pthread_t thread_id;

    char* arg = "STAY HEALTY";
    pthread_create(&thread_id, NULL, thread_func, arg);

    // wait for end of thread
    void* ret;
    pthread_join(thread_id, &ret);

    printf("Main: My son respond: %d\n", *((int*)ret));
    free(ret);


    return 0;
}