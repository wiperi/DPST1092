# return the number of peaks in an array of integers
#
# A peak is a value that is both preceded and succeeded
# by a value smaller than itself
#
# ie:
# Both the value before and the value after the current value
# are smaller than the current value
#
# eg:
# [1, 3, 2, 5, 4, 4, 9, 0, 1, -9, -5, -7]
#     ^     ^        ^     ^       ^
# The value 3, 5, 9, 1, -5 are all peaks in this array
# So your function should return 5

.text
.globl final_q4

final_q4:
	# YOU DO NOT NEED TO CHANGE THE LINES ABOVE HERE


	# REPLACE THIS LINE WITH YOUR CODE
	move	$t0, $a0	# array
	move	$t1, $a1	# length
	li	$v0, 42

	jr	$ra


# ADD ANY EXTRA FUNCTIONS BELOW THIS LINE
