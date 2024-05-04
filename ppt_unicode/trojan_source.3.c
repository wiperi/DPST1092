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
    // These three variables look to be all the same
    // But they are not, they are all different variables
    // Each variable uses a different unicode character for the `o`
    // The first variable uses the "latin small letter o" (U+006F)
    // The second variable uses the "armenian small letter o" (U+0585)
    // The third variable uses the "cyrillic small letter o" (U+043E)
    // They all look the same, but the C compiler treats them as different variables

    int total;        // latin
    int tօtal;        // armenian
    int tоtal = -666; // cyrillic

    total = 100; // latin
    printf("total = %d\n", total); // latin

    tօtal = 999; // armenian
    printf("total = %d\n", total); // latin

    total = tօtal; // latin = armenian
    printf("total = %d\n", tоtal); // cyrillic

    printf("total = %d\n", tօtal); // armenian

    return 0;
}
