EXERCISES	+= fix_race
CLEAN_FILES	+= fix_race fix_race.o test_fix_race.o

fix_race:	fix_race.c test_fix_race.c
	$(CC) -pthread fix_race.c test_fix_race.c -o fix_race
