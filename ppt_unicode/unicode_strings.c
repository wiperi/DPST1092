#include <stdio.h>
#include <string.h>

#define cmp(s1, s2) strcmp(s1, s2) ? "Not Equal" : "Equal"

int main(void) {
    char *string1 = "Hello World";         // normal ASCII
    char *string2 = "Hellо Wоrld";         // These are not latin o's (cyrillic)
    char *string3 = "Hellⲟ Wօrld";         // These are also not latin o's (coptic and armenian)
    char *string4 = "Ⓗⓔⓛⓛⓞ Ⓦⓞⓡⓛⓓ"; // letters in circles
    char *string5 = "Hëllo World";         // e with a diaeresis (one character)
    char *string6 = "Hëllo World";         // latin small letter e followed by a combining diaeresis (two characters)

    // The command `unicode` can be used to see the unicode code points of a string
    // eg `unicode -sm0 "Hello World" --brief` will display:
    /*
        H U+0048 LATIN CAPITAL LETTER H
        e U+0065 LATIN SMALL LETTER E
        l U+006C LATIN SMALL LETTER L
        l U+006C LATIN SMALL LETTER L
        ⲟ U+2C9F COPTIC SMALL LETTER O
        U+0020 SPACE
        W U+0057 LATIN CAPITAL LETTER W
        օ U+0585 ARMENIAN SMALL LETTER OH
        r U+0072 LATIN SMALL LETTER R
        l U+006C LATIN SMALL LETTER L
        d U+0064 LATIN SMALL LETTER D
    */

    // Even though the strings look the same, they are not the same
    // all of the strings contain different unicode characters
    // so comparing them with strcmp will return false

    printf("string1 == string2: %s\n", cmp(string1, string2));
    printf("string1 == string3: %s\n", cmp(string1, string3));
    printf("string1 == string4: %s\n", cmp(string1, string4));
    printf("string1 == string5: %s\n", cmp(string1, string5));
    printf("string1 == string6: %s\n", cmp(string1, string6));
    printf("string2 == string3: %s\n", cmp(string2, string3));
    printf("string2 == string4: %s\n", cmp(string2, string4));
    printf("string2 == string5: %s\n", cmp(string2, string5));
    printf("string2 == string6: %s\n", cmp(string2, string6));
    printf("string3 == string4: %s\n", cmp(string3, string4));
    printf("string3 == string5: %s\n", cmp(string3, string5));
    printf("string3 == string6: %s\n", cmp(string3, string6));
    printf("string4 == string5: %s\n", cmp(string4, string5));
    printf("string4 == string6: %s\n", cmp(string4, string6));
    printf("string5 == string6: %s\n", cmp(string5, string6));

    char _; scanf("%c", &_);

    // the strlen function does not count the number of characters in a string
    // it counts the number of bytes in a string
    // for ASCII strings, the number of bytes is the same as the number of characters
    // but for UTF-8 strings, the number of bytes is not the same as the number of characters

    printf("string1: %lu\n", strlen(string1));
    printf("string2: %lu\n", strlen(string2));
    printf("string3: %lu\n", strlen(string3));
    printf("string4: %lu\n", strlen(string4));
    printf("string5: %lu\n", strlen(string5));
    printf("string6: %lu\n", strlen(string6));
}
