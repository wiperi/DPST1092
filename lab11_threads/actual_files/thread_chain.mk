EXERCISES	+= thread_chain
CLEAN_FILES	+= thread_chain thread_chain.o test_thread_chain.o

thread_chain:	thread_chain.c test_thread_chain.c
	$(CC) -pthread thread_chain.c test_thread_chain.c -o thread_chain -Wl,--wrap=pthread_create
