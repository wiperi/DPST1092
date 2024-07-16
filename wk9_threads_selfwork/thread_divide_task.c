/**
 * Introduction:
 *
 * Use multiple threads to calculate the sum from [0, n]. Each thread handle n/n_threads integers.
 */
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct job {
    long start, end;
    double sum;
};

void* thread_sum(void* arg) {

    struct job* j = (struct job*)arg;
    for (long i = j->start + 1; i <= j->end; i++) {
        j->sum += i;
    }
    printf("Thread: sum from %4li to %4li, resulting sum is %6lf\n", j->start + 1, j->end, j->sum);

    return NULL;
}

int main() {

    int n_threads, max_int;
    printf("Sum from 0 to ?, using ? threads: ");
    scanf(" %d %d", &max_int, &n_threads);

    // build arguments
    pthread_t id[n_threads];
    struct job jobs[n_threads];

    int int_per_threads;
    if (max_int % n_threads == 0) {
        int_per_threads = max_int / n_threads;
    } else {
        int_per_threads = max_int / n_threads + 1;
    }
    printf("Integer each threads will handle is %4d\n", int_per_threads);

    for (int i = 0; i < n_threads; i++) {
        // init jobs
        jobs[i].start = i * int_per_threads;           // 0, 2, 4
        jobs[i].end = jobs[i].start + int_per_threads; // 2, 4, 6
        if (jobs[i].end > max_int) {                   // cast 6 to 5
            jobs[i].end = max_int;
        }

        jobs[i].sum = 0;
    }

    // create threads
    for (int i = 0; i < n_threads; i++) {
        pthread_create(&id[i], NULL, thread_sum, &jobs[i]);
    }
    for (int i = 0; i < n_threads; i++) {
        pthread_join(id[i], NULL);
    }

    // compute overall result
    double overall_sum = 0;
    for (int i = 0; i < n_threads; i++) {
        overall_sum += jobs[i].sum;
    }
    printf("\nOverall sum: %lf\n", overall_sum);

    return 0;
}