#include <stdio.h>
#include <string.h>

// most modern text editors will show you the invisible characters in this file
// because this file demonstrates a very real security vulnerability
// In vscode you can disable this by adding the following to your settings.json
//      "editor.renderWhitespace": "none",
//      "editor.unicodeHighlight.ambiguousCharacters": false,
//      "editor.unicodeHighlight.invisibleCharacters": false,
//      "editor.unicodeHighlight.nonBasicASCII": false,
//      "editor.renderControlCharacters": false,
// But you should immediately re-enable it after you have finished reading this file

int main(void) {

    // This variable doesn't look like it is valid C
    // As variable must be single words
    // replacing the space with an underscore `_` would make it valid

    // EXCEPT that the space is not a space
    // it's the "HALFWIDTH HANGUL FILLER" character
    // the HALFWIDTH HANGUL FILLER is rather special
    // as it is one of very few characters that are invisible
    // ie don't have a visible glyph
    // yet isn't a whitespace character (has the WhiteSpace=yes UNICODE property)
    // This means that C allows it to be used in variable names

    int helloﾠworld = 20;
    printf("helloﾠworld = %d\n", helloﾠworld);

    // FULLWIDTH HYPHEN-MINUS can be used to make a variable name
    // that looks like they have a hyphen in them

    int hello－world = 20;
    printf("hello－world = %d\n", hello－world);

    // Please never actually use these characters in variable names

    return 0;
}
