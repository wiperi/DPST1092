EXERCISES += railroad_runners
CLEAN_FILES += railroad_runners

railroad_runners: railroad_runners.c
	$(CC) -o $@ $<

.PHONY: submit give

submit give: railroad_runners.s
	give cs1521 ass1_railroad_runners railroad_runners.s

.PHONY: test autotest

test autotest: railroad_runners.s
	1521 autotest railroad_runners
