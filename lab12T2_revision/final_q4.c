/**
 * return the number of peaks in an array of integers
 *
 * A peak is (in this case)
 * a value that is both preceded and succeeded by a value smaller than itself
 *
 * ie:
 * Both the value before and the value after the current value
 * are smaller than the current value
 *
 * eg:
 * [1, 3, 2, 5, 4, 4, 9, 0, 1, -9, -5, -7]
 *     ^     ^        ^     ^       ^
 * The value 3, 5, 9, 1, -5 are all peaks in this array
 * So your function should return 5
**/

#include <stdio.h>

int final_q4(int array[], int length) {
    int total = 0;
    int i = 1;

    while (i < length - 1) {
        if (array[i] > array[i - 1] && array[i] > array[i + 1]) {
            total++;
        }
        i++;
    }

    return total;
}
