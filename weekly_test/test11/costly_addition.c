#include <pthread.h>
#include <stdlib.h>

void* increment_and_sleep(void* arg);

void costly_addition(int num) {
    // TODO: Implement this function and remove this comment.

    // create num threads to increment data
    pthread_t threads[num];
    for (int i = 0; i < num; i++) {
        pthread_create(&threads[i], NULL, increment_and_sleep, NULL);
    }

    // wait for all threads to finish
    for (int i = 0; i < num; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
