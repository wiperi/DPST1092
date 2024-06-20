///////////////////////////////////////////////////////////////////////////////
// DPST1092 24T2 --- Assignment 2: `space', a simple file archiver           //
//                                                                           //
//                                                                           //
///////////////////// YOU DO NOT NEED TO MODIFY THIS FILE. ////////////////////

////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////


// This file provides a main function & argument processing


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <err.h>
#include <sysexits.h>

#include "space.h"

enum a_mode {
    A_NONE = 0,  /**< No mode provided. */
    A_CHECK,     /**< Invoked with `-C'. */
    A_LIST,      /**< Invoked with `-l'. */
    A_LIST_LONG, /**< Invoked with `-L'. */
    A_EXTRACT,   /**< Invoked with `-e'. */
    A_CREATE,    /**< Invoked with `-c'. */
    A_APPEND,    /**< Invoked with `-a'. */
};

typedef struct args {
    enum a_mode mode;
    enum galaxy_fmt format; /**< Format to archive into. */
    char *galaxy_file;         /**< Archive file name. */
    size_t n_paths;         /**< Number of file paths to archive. */
    char **paths;           /**< Array of file paths to archive. */
} args;

static const char *a_mode_name[] = {
    [A_CHECK]     = "check",
    [A_LIST]      = "list",
    [A_LIST_LONG] = "list-long",
    [A_EXTRACT]   = "extract",
    [A_CREATE]    = "create",
    [A_APPEND]    = "append",
};

static args space_parse_args(int, char **);
static void __attribute__((noreturn)) usage_short(void);
static void __attribute__((noreturn)) usage_long(void);

////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    struct args arguments = space_parse_args(argc, argv);

    switch (arguments.mode) {
    case A_CHECK: {
        check_galaxy(arguments.galaxy_file);
        break;
    }
    case A_LIST: {
        list_galaxy(arguments.galaxy_file, false);
        break;
    }
    case A_LIST_LONG: {
        list_galaxy(arguments.galaxy_file, true);
        break;
    }
    case A_EXTRACT: {
        extract_galaxy(arguments.galaxy_file);
        break;
    }
    case A_CREATE: {
        create_galaxy(
            arguments.galaxy_file, false, arguments.format,
            arguments.n_paths, arguments.paths
        );
        break;
    }
    case A_APPEND: {
        create_galaxy(
            arguments.galaxy_file, true, arguments.format,
            arguments.n_paths, arguments.paths
        );
        break;
    }
    default: {
        // unreachable
    }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////

#define INVALID_MODE_MESSAGE \
    "Requires exactly one of: 'C|check', 'l|list', " \
    "'L|list-long', 'c|create', 'a|append', 'x|extract'"

struct args space_parse_args(int argc, char **argv) {
    struct args arguments = {
        .mode     = A_NONE,
        .format   = STAR_FMT_8,
        .galaxy_file = NULL,
        .n_paths  = 0,
        .paths    = NULL,
    };

    opterr = 0;
    int opt;
    while ((opt = getopt_long(
                argc, argv, "678acClLxh",
                (struct option[]){
                    (struct option){ "6-bit-format", no_argument, 0, '6' },
                    (struct option){ "7-bit-format", no_argument, 0, '7' },
                    (struct option){ "8-bit-format", no_argument, 0, '8' },
                    (struct option){ "append",       no_argument, 0, 'a' },
                    (struct option){ "create",       no_argument, 0, 'c' },
                    (struct option){ "check",        no_argument, 0, 'C' },
                    (struct option){ "list",         no_argument, 0, 'l' },
                    (struct option){ "list-long",    no_argument, 0, 'L' },
                    (struct option){ "extract",      no_argument, 0, 'x' },
                    (struct option){ "help",         no_argument, 0, 'h' },
                    (struct option){ 0,              0,           0,  0  },
                },
                NULL)) != -1) {
        switch (opt) {
        case 'h': {
            usage_long();
        }
        case '6': {
            arguments.format = STAR_FMT_6;
            break;
        }
        case '7': {
            arguments.format = STAR_FMT_7;
            break;
        }
        case '8': {
            arguments.format = STAR_FMT_8;
            break;
        }
        case 'C': {
            if (arguments.mode != A_NONE) {
                warnx(INVALID_MODE_MESSAGE);
                warnx("Both \"%s\" and \"%s\" were given.",
                      a_mode_name[arguments.mode], a_mode_name[A_CHECK]);
                usage_short();
            }
            arguments.mode = A_CHECK;
            break;
        }
        case 'l': {
            if (arguments.mode != A_NONE) {
                warnx(INVALID_MODE_MESSAGE);
                warnx("Both \"%s\" and \"%s\" were given.",
                      a_mode_name[arguments.mode], a_mode_name[A_LIST]);
                usage_short();
            }
            arguments.mode = A_LIST;
            break;
        }
        case 'L': {
            if (arguments.mode != A_NONE) {
                warnx(INVALID_MODE_MESSAGE);
                warnx("Both \"%s\" and \"%s\" were given.",
                      a_mode_name[arguments.mode], a_mode_name[A_LIST_LONG]);
                usage_short();
            }
            arguments.mode = A_LIST_LONG;
            break;
        }
        case 'c': {
            if (arguments.mode != A_NONE) {
                warnx(INVALID_MODE_MESSAGE);
                warnx("Both \"%s\" and \"%s\" were given.",
                      a_mode_name[arguments.mode], a_mode_name[A_CREATE]);
                usage_short();
            }
            arguments.mode = A_CREATE;
            break;
        }
        case 'a': {
            if (arguments.mode != A_NONE) {
                warnx(INVALID_MODE_MESSAGE);
                warnx("Both \"%s\" and \"%s\" were given.",
                      a_mode_name[arguments.mode], a_mode_name[A_APPEND]);
                usage_short();
            }
            arguments.mode = A_APPEND;
            break;
        }
        case 'x': {
            if (arguments.mode != A_NONE) {
                warnx(INVALID_MODE_MESSAGE);
                warnx("Both \"%s\" and \"%s\" were given.",
                      a_mode_name[arguments.mode], a_mode_name[A_EXTRACT]);
                usage_short();
            }
            arguments.mode = A_EXTRACT;
            break;
        }
        default: {
            warnx("Unknown option \"%d\" given.", optopt);
            usage_short();
        }
        }
    }

    if (arguments.mode == A_NONE) {
        warnx(INVALID_MODE_MESSAGE);
        warnx("None were given");
        usage_short();
    }

    if (optind == argc) {
        warnx("Requires exactly one archive (.galaxy) file");
        warnx("None were given");
        usage_short();
    }

    arguments.galaxy_file = argv[optind++];

    if (arguments.mode == A_CREATE || arguments.mode == A_APPEND) {
        if (optind == argc) {
            warnx("\"%s\" Requires one or more files to archive",
                  a_mode_name[arguments.mode]);
            warnx("None were given");
            usage_short();
        }
        arguments.n_paths = argc - optind;
        arguments.paths = &(argv[optind]);
    }

    return arguments;
}

static const char *short_usage_message =
    "usage: space [<FORMAT>] <MODE> <ARCHIVE-FILE> [<FILE...>]";

/// Print a short usage message.
static void __attribute__((noreturn)) usage_short(void) {
    errx(EX_USAGE, "%s", short_usage_message);
}

static const char *long_usage_message =
    "space --- a simple file archiver\n"
    "\n"
    "USAGE:\n"
    "    space [<FORMAT>] <MODE> <ARCHIVE-FILE> [<FILE...>]\n"
    "\n"
    "COMMON MODES:\n"
    "    -l, --list\n"
    "        list basic information about all files in ARCHIVE-FILE.\n"
    "    -L, --list-long\n"
    "        list additional information about all files in ARCHIVE-FILE.\n"
    "    -C, --check\n"
    "        check hash of ARCHIVE-FILE.\n"
    "    -c, --create\n"
    "        create ARCHIVE-FILE containing the listed FILEs.\n"
    "    -a, --append\n"
    "        append the listed FILEs to ARCHIVE-FILE.\n"
    "    -x, --extract\n"
    "        extract all files from ARCHIVE-FILE\n"
    "\n"
    "COMMON FORMATS:\n"
    "    -6\n"
    "        create or append to ARCHIVE-FILE using 6-bit format\n"
    "    -7\n"
    "        create or append to ARCHIVE-FILE using 7-bit format\n"
    "    -8\n"
    "        create or append to ARCHIVE-FILE using 8-bit format [DEFAULT]\n"
    "\n"
    "For more information, see the assignment specification, at\n"
    "    <https://www.cse.unsw.edu.au/~cs1521/24T1/assignments/ass2/index.html>\n";

/// Print a longer, more helpful usage message.
static void __attribute__((noreturn)) usage_long(void) {
    errx(EX_USAGE, "%s", long_usage_message);
}

////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
// THIS FILE IS NOT SUBMITTED AND WILL BE PROVIDED AS IS DURING TESTING AND MARKING //
////////////////////////////// DO NOT CHANGE THIS FILE. //////////////////////////////
