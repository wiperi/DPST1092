EXERCISES	+= supp_q7
CLEAN_FILES	+= supp_q7

supp_q7:	supp_q7.c supp_q7_main.c

test_supp_q7:
	make supp_q7
	./supp_q7 3 < supp_q7_examples/more_sequences.txt