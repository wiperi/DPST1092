// swap pairs of bits of a 64-bit value, using bitwise operators

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "thread_chain.h"

#define THREAD_CHAIN_LEN 50

pthread_t hello_handles [THREAD_CHAIN_LEN];
pthread_t create_handles[THREAD_CHAIN_LEN];


int main() {
	my_main();

	for (int i = 0; i < THREAD_CHAIN_LEN; i++) {
		if (!hello_handles[i]) {
			fprintf(stderr, "ERROR: thread_hello was called less than 50 times!\n");
			fprintf(stderr, "help: it was only called %d time(s)\n", i);
			fprintf(stderr, "the program will now exit\n");
			exit(1);
		}
	}

	printf("program succeeded!\n");
}

void thread_hello(void) {
	pthread_t thread = pthread_self();
	for (int i = 0; i < THREAD_CHAIN_LEN; i++) {
		if (!hello_handles[i]) {
			hello_handles[i] = thread;
			printf("Hello from thread %02d!\n", i + 1);
			return;
		}

		if (pthread_equal(thread, hello_handles[i])) {
			fprintf(stderr, "ERROR: thread_hello called twice from the same thread!\n");
			fprintf(stderr, "the program will now exit\n");
			exit(1);
		}
	}

	fprintf(stderr, "ERROR: thread_hello called more than 50 times!\n");
	fprintf(stderr, "the program will now exit\n");
	exit(1);
}

extern int __real_pthread_create(
	pthread_t *, pthread_attr_t *, void *(*)(void *), void *
);

int __wrap_pthread_create(
	pthread_t *thread,
	pthread_attr_t *attr,
	void *(*fn)(void *data),
	void *data
) {
	pthread_t current_thread = pthread_self();
	for (int i = 0; i < THREAD_CHAIN_LEN; i++) {
		if (!create_handles[i]) {
			create_handles[i] = current_thread;
			break;
		}

		if (pthread_equal(current_thread, create_handles[i])) {
			fprintf(stderr, "ERROR: pthread_create called twice from the same thread!\n");
			fprintf(stderr, "help: you need to create a chain of threads, where\n");
			fprintf(stderr, "      each thread creates just one thread, and that\n");
			fprintf(stderr, "      thread creates a new thread, and so on...\n");
			fprintf(stderr, "the program will now exit\n");
			exit(1);
		}
	}

	return __real_pthread_create(thread, attr, fn, data);
}
