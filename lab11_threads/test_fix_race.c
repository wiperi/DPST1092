// swap pairs of bits of a 64-bit value, using bitwise operators

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *thread_run(void *data);
int get_global_counter(void);


int main(int argc, char *argv[]) {
	if (!argv[0] || !argv[1] || !argv[2]) {
		fprintf(stderr, "Usage: %s <n threads> <n increments per thread>\n", argv[0]);
		return 1;
	}

	unsigned long n_threads	   = strtoul(argv[1], NULL, 0);
	unsigned long n_increments = strtoul(argv[2], NULL, 0);

	pthread_t *threads = malloc(n_threads * sizeof(pthread_t));
	for (int i = 0; i < n_threads; i++) {
		pthread_create(&threads[i], NULL, thread_run, &n_increments);
	}

	for (int i = 0; i < n_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	free(threads);

	printf("Global counter result: %d\n", get_global_counter());}
