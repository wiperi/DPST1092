#include <dirent.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define EXE_PATH "/usr/bin/file"

extern char** environ;

int main(int argc, char const* argv[]) {

    char* file_path = argv[1];

    /************************************************************************
     * Prodess
     ************************************************************************/
    pid_t pid;
    char* arg[] = {EXE_PATH, file_path, NULL}; // end with NULL
    if (posix_spawn(&pid, EXE_PATH, NULL, NULL, arg, environ) == 0) {
        waitpid(pid, NULL, 0);
    } else {
        perror("posix_spawn");
        return 1;
    }

    /************************************************************************
     * stat
     ************************************************************************/
    struct stat st;
    stat(file_path, &st);
    if (S_ISREG(st.st_mode)) {
        // is regular file
    }
    if (S_ISDIR(st.st_mode)) {
        // is directory
    }
    st.st_size; // file size
    st.st_mode; // permissions

    /************************************************************************
     * opendir
     ************************************************************************/
    DIR* dir = opendir(file_path);
    struct dirent* entry;
    entry->d_name; // file name
    entry->d_type; // file type
    if (entry->d_type == DT_REG) {
        // is regular file
    }
    while ((entry = readdir(dir)) != NULL) {
        // do something
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            // skip . and ..
            continue;
        }
        // build new sub-path
        char* next_path = malloc(1024);
        sprintf(next_path, "%s/%s", file_path, ent->d_name);
        free(next_path);
    }

    return 0;
}

/************************************************************************
 * UTF8
 ************************************************************************/
int valid_utf8(char* input) {
    
    uint8_t ch;
    int i = 0;
    while (input[i] != '\0')
    {
        ch = input[i];

        // is head valid?
        int tail = 0;
        if ((ch >> 7) == 0) {
            ;
        } else if ((ch >> 3) == 0b11110) {
            tail = 3;
        } else if ((ch >> 4) == 0b1110) {
            tail = 2;
        } else if ((ch >> 5) == 0b110) {
            tail = 1;
        } else {
            // invalid
            return i;
        }

        // is tail valid?
        if (tail != 0) {
            for (int j = 0; j < tail; j++) {
                i++;
                ch = input[i];

                if ((ch >> 6) == 0b10) {
                    ;
                } else {
                    // invalid
                    return i;
                }
            }
        }

        i++;
    }
    
    return -1;
}