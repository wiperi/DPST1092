/**
 * Introduction:
 *
 * Use mutex to let multiple threads correctily access one global var
 */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int score = 0;

void* thread_add_10000(void* a) {

    for (int i = 0; i < 10000; i++) {

        atomic_fetch_add(&score, 1);

    }

    return NULL;
}

int main() {

    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, thread_add_10000, NULL);

    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, thread_add_10000, NULL);

    // wait for the 2 threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    printf("%d\n", score); // 20000

    return 0;
}