#include <stdio.h>
#include <string.h>
#include <assert.h>

unsigned long utf8_strlen(char *string) {
    unsigned long num_code_points = 0;
    for (char *code_point = string; *code_point;) {
        if ((*code_point & 0xF8) == 0xF0) {
            // 4-byte head byte
            code_point += 4;
        } else if ((*code_point & 0xF0) == 0xE0) {
            // 3-byte head byte
            code_point += 3;
        } else if ((*code_point & 0xE0) == 0xC0) {
            // 2-byte head byte
            code_point += 2;
        } else if ((*code_point & 0xC0) == 0x80) {
            // INVALID STRING
            // tail byte - should not be here
            // as we should be moving from head byte to head byte
            fprintf(stderr, "Invalid UTF-8 string: \"%s\"\n", string);
            fprintf(stderr, "Found a tail byte when head byte was expected\n");
            assert(0);
        } else if ((*code_point & 0x80) == 0x00) {
            // ASCII
            code_point += 1;
        } else {
            // INVALID STRING
            // this is not a valid UTF-8 byte
            fprintf(stderr, "Invalid UTF-8 string: \"%s\"\n", string);
            fprintf(stderr, "Head byte indicates invalid length\n");
            assert(0);
        }
        num_code_points++;
    }

    return num_code_points;
}

int main(void) {
    char *string1 = "Hello World";
    char *string2 = "Hellо Wоrld";
    char *string3 = "Hellⲟ W𐓪rld";
    char *string4 = "Ⓗⓔⓛⓛⓞ Ⓦⓞⓡⓛⓓ";
    char *string5 = "Hëllo World";
    char *string6 = "Hëllo World";

    printf("\"%s\": strlen=%lu, utf8_strlen=%lu\n", string1, strlen(string1), utf8_strlen(string1));
    printf("\"%s\": strlen=%lu, utf8_strlen=%lu\n", string2, strlen(string2), utf8_strlen(string2));
    printf("\"%s\": strlen=%lu, utf8_strlen=%lu\n", string3, strlen(string3), utf8_strlen(string3));
    printf("\"%s\": strlen=%lu, utf8_strlen=%lu\n", string4, strlen(string4), utf8_strlen(string4));
    printf("\"%s\": strlen=%lu, utf8_strlen=%lu\n", string5, strlen(string5), utf8_strlen(string5));
    printf("\"%s\": strlen=%lu, utf8_strlen=%lu\n", string6, strlen(string6), utf8_strlen(string6));
}
