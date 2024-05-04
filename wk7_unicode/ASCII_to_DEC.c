#include <assert.h>

/**
 * @brief Convert an ASCII character to a decimal digit
 *
 * Subtract '0' from the character to convert it to a decimal digit.
 *
 * @param c - character to convert
 * @return int - decimal digit
 */
int ascii_to_dec_subtraction(char c) {
    return c - '0';
}

/**
 * @brief Convert a decimal digit to an ASCII character
 *
 * Add '0' to the digit to convert it to an ASCII character.
 *
 * @param i - decimal digit to convert
 * @return char - ASCII character
 */
char dec_to_ascii_addition(int i) {
    return i + '0';
}

/**
 * @brief Convert an ASCII character to a decimal digit
 *
 * Bitwise AND with 0x0F to convert it to a decimal digit.
 * Keeping only the last 4 bits of the character.
 *
 * @param c - character to convert
 * @return int - decimal digit
 */
int ascii_to_dec_bitwise(char c) {
    return c & 0x0F;
}

/**
 * @brief Convert a decimal digit to an ASCII character
 *
 * Bitwise OR with 0x30 to convert it to an ASCII character.
 * Setting the 5th and 6th bits of the character.
 *
 * @param i - decimal digit to convert
 * @return char - ASCII character
 */
char dec_to_ascii_bitwise(int i) {
    return i | 0x30;
}

int main(void) {
    assert(5 == ascii_to_dec_subtraction('5'));
    assert(5 == ascii_to_dec_bitwise('5'));
    assert(ascii_to_dec_subtraction('5') == ascii_to_dec_bitwise('5'));

    assert('5' == dec_to_ascii_addition(5));
    assert('5' == dec_to_ascii_bitwise(5));
    assert(dec_to_ascii_addition(5) == dec_to_ascii_bitwise(5));
}
