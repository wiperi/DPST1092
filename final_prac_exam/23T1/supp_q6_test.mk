EXERCISES	+= supp_q6, test_supp_q6
CLEAN_FILES	+= supp_q6

supp_q6:	supp_q6.c

test_supp_q6:
	seq 1 15 > supp_q6_input
	supp_q6 supp_q6_input 3
