#include <stdio.h>

int is_vowel(int ch) {
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        return 1;
    else
        return 0;
}

int main(int argc, char *argv[], char *envp[]) {
    
    int ch;

    while ((scanf("%c", &ch)) == 1) {
        if (!is_vowel(ch)) {
            printf("%c", ch);
        }
    }
    
}