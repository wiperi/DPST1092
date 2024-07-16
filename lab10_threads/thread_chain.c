#include <pthread.h>
#include "thread_chain.h"

void *my_thread(void *data) {

    // base case
    int* n_time = (int*) data;
    if (*n_time == 0) {
        return NULL;
    }

    // update times
    (*n_time)--;
    
    thread_hello();

    // recursive call
    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, data);

    pthread_join(thread_handle, NULL);
    
    return NULL;
}

void my_main(void) {

    int n_time = 50;
    
    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, &n_time);

    pthread_join(thread_handle, NULL);
}
