#include <pthread.h>
#include "thread_chain.h"

void *my_thread(void *data) {

    // base case
    int* times = (int*) data;
    if (*times == 0) {
        return NULL;
    }

    // update times
    (*times)--;
    
    thread_hello();

    // recursive call
    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, data);

    pthread_join(thread_handle, NULL);
    
    return NULL;
}

void my_main(void) {

    int times = 50;
    
    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, &times);

    pthread_join(thread_handle, NULL);
}
