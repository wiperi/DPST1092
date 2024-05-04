#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * @brief Convert a string to uppercase
 *
 * Subtract 32 from each lowercase letter to convert it to uppercase.
 *
 * @param s - string to convert
 * @return char* - pointer to the converted string (same as input pointer)
 */
char *to_upper_subtraction(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 32;
        }
    }
    return s;
}

/**
 * @brief Convert a string to uppercase
 *
 * Bitwise AND with 0xDF to convert lowercase letters to uppercase.
 *
 * @param s - string to convert
 * @return char* - pointer to the converted string (same as input pointer)
 */
char *to_upper_bitwise(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] &= ~0x20;
        }
    }
    return s;
}

/**
 * @brief Compare two strings, ignoring case
 *
 * This is already implemented in the standard library as strcasecmp().
 *
 * @param s1 - first string
 * @param s2 - second string
 * @return true - if the strings are equal, ignoring case
 * @return false - if the strings are not equal
 */
bool case_insensitive_compare_bitwise(char *s1, char *s2) {
    for (int i = 0; s1[i] && s2[i]; i++) {
        if (isalpha(s1[i]) && isalpha(s2[i])) {
            // Alphabetical character
            // Compare ignoring case
            // Convert both characters to uppercase lowercase
            // by inserting a 1 in the 6th bit then comparing
            if ((s1[i] | 0x20) != (s2[i] | 0x20)) {
                return false;
            }
        } else {
            // Non-Alphabetical character
            // Normal comparison
            if (s1[i] != s2[i]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    char s1[] = "Hello, World!";
    char s2[] = "Hello, World!";
    assert(0 == strcmp("HELLO, WORLD!", to_upper_subtraction(s1)));
    assert(0 == strcmp("HELLO, WORLD!", to_upper_bitwise(s2)));

    char s3[] = "HeLLo, WOrLD!";
    char s4[] = "hEllo, WORld!";
    assert(case_insensitive_compare_bitwise(s3, s4));
}
