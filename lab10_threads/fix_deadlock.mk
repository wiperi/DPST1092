EXERCISES	+= fix_deadlock
CLEAN_FILES	+= fix_deadlock fix_deadlock.o test_fix_deadlock.o

fix_deadlock:	fix_deadlock.c test_fix_deadlock.c
	$(CC) -pthread fix_deadlock.c test_fix_deadlock.c -o fix_deadlock
