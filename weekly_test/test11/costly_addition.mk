EXERCISES	+= costly_addition
CLEAN_FILES	+= costly_addition costly_addition.o test_costly_addition.o

costly_addition:	costly_addition.c test_costly_addition.c
	$(CC) -pthread costly_addition.c test_costly_addition.c -o costly_addition
