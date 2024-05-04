#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// most modern text editors will show you the invisible characters in this file
// because this file demonstrates a very real security vulnerability
// In vscode you can disable this by adding the following to your settings.json
//      "editor.renderWhitespace": "none",
//      "editor.unicodeHighlight.ambiguousCharacters": false,
//      "editor.unicodeHighlight.invisibleCharacters": false,
//      "editor.unicodeHighlight.nonBasicASCII": false,
//      "editor.renderControlCharacters": false,
// But you should immediately re-enable it after you have finished reading this file


bool strings_are_equal(char *s1, char *s2) {
    // To see what this function is actually doing
    // uncomment the following line:
    // printf("Comparing \"%s\" and \"%s\"\n", s1, s2);
    return strcmp(s1, s2) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        printf("Usage: %s <access_level>\n", argv[0]);
        printf("Access levels:\n");
        printf("0: user, 1: admin\n");
        return 1;
    }

    char *access_levels[] = {
        "user",
        "admin"
    };

    char *endptr;
    long selected_access_level = strtol(argv[1], &endptr, 0);

    if (*endptr != '\0')
    {
        printf("Invalid access level: %s\n", argv[1]);
        printf("Access levels:\n");
        printf("0: user, 1: admin\n");
        return 1;
    }

    if (selected_access_level < 0 || selected_access_level > 1)
    {
        printf("Invalid access level: %ld\n", selected_access_level);
        printf("Access levels:\n");
        printf("0: user, 1: admin\n");
        return 1;
    }

    char *current_access_level = access_levels[selected_access_level];

    printf("Current access level: %s\n", current_access_level);

    // with invisible characters not visible
    // this next line will likely look like:
    //      if (!strings_are_equal(current_access_level, "user")) // Check if admin
    // But that's not actully what it is
    // the real code is:
    //      if (!strings_are_equal(current_access_level, "user <invisible-characters>// Check if admin<invisible-characters>"))
    // The invisible characters here are:
    //      the RIGHT-TO-LEFT OVERRIDE (U+202E),
    //      the LEFT-TO-RIGHT ISOLATE (U+2066),
    //      the POP DIRECTIONAL ISOLATE (U+2069),
    // In that order
    // These characters tell the text editor to render the text in a forced direction
    // Instead of the normal direction of the text (left-to-right in the western world, right-to-left in the arabic world)
    // Forcing the text to be rendered in a different direction is a common way to make text appear to be something it is not
    // Like in tis case where what looks like a comment is actually part of the string
    if (!strings_are_equal(current_access_level, "user‮ ⁦// Check if admin⁩ ⁦"))
    {
        printf("Hello admin.\n");
    }
    else
    {
        printf("Hello user.\n");
    }

    return 0;
}
