//
// DPST1092 Lab 01 Exercise - no vowels
// 
// Introduction:
// Don't print vowels.
// 
// Reference
// 
// 
// Authors:
// Tianyang Chen (z5567323@unsw.edu.au)
// 
// Written: 8/5/2024
//
#include <stdio.h>

int is_vowel(int ch) {
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        return 1;
    else if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        return 1;
    else
        return 0;
}

int main(int argc, char* argv[], char* envp[]) {

    char ch = 0;

    while ((scanf("%c", &ch)) == 1) {
        if (!is_vowel(ch)) {
            printf("%c", ch);
        }
    }
}