/**
 * Introduction:
 * 
 * Create multiple threads, show that they runs concurrently with main.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void* thread_count(void* arg) {

    pthread_t* id_ptr = (pthread_t*)arg;

    for (int i = 10; i >= 1; i--) {
        printf("Thrad %lu counting [%d]\n", *id_ptr, i);
        sleep(1);
    }
}

int main(int argc, char* argv[], char* envp[]) {

    pthread_t id[10];

    for (int i = 0; i < 10; i++) {
        pthread_create(&id[i], NULL, thread_count, &id[i]);

        // concurrently run with threads        
        printf("Main saying hello.\n");
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(id[i], NULL);
        printf("Reaps thrad %lu\n", id[i]);
    }

    return 0;
}