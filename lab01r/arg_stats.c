//
// DPST1092 Lab 01 Exercise - arg stat
// 
// Introduction:
// extract some statistical info from cmd args
// 
// Reference
// 
// 
// Authors:
// Tianyang Chen (z5567323@unsw.edu.au)
// 
// Written: 5/8/2024
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s NUMBER [NUMBER ...]\n", argv[0]);
		return 1;
	}

	int min = atoi(argv[1]);
	int max = atoi(argv[1]);
	int sum = 0;
	int product = 1;

	for (int i = 1; i < argc; i++) {
		int num = atoi(argv[i]);
		if (num < min) {
			min = num;
		}
		if (num > max) {
			max = num;
		}
		sum += num;
		product *= num;
	}

	double mean = (double) sum / (argc - 1);

	printf("MIN:  %d\n", min);
	printf("MAX:  %d\n", max);
	printf("SUM:  %d\n", sum);
	printf("PROD: %d\n", product);
	printf("MEAN: %d\n", (int) mean);

	return 0;
}
