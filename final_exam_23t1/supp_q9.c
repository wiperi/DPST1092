// DPST1092 23T1, supp exam, question 9
// Recursively search for the largest file in the current
// directory, and invoke `file` on it.

#include <dirent.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SPAWN_EXECUTABLE "/usr/bin/file"

// You may find the following struct datatype useful.
// You do not have to use it if you don't want to.
struct filesize {
    char *path;
    off_t size;
};

static struct filesize file;

extern char **environ;

// Add any function definitions you need here.
void dfs(char *path);

void supp_q9(char *directory) {
    // Modify the function below.
    dfs(directory);

    pid_t pid;
    char *arg[] = {SPAWN_EXECUTABLE, file.path, NULL};
    if (posix_spawn(&pid, SPAWN_EXECUTABLE, NULL, NULL, arg, environ) == 0) {
        waitpid(pid, NULL, 0);
    } else {
        perror("posix_spawn");
        return;
    }
    printf("is the largest file in this subtree, with size %ld bytes.\n",
           file.size);
}

// You may implement your own functions below.

// void dfs(int* root) {
//     if (head == NULL) {
//         return;
//     }

//     for head in head.sons:
//         dfs(head);
// }

void dfs(char *path) {
    struct stat st;
    if (stat(path, &st)) {
        perror("stat: ");
        exit(1);
    }
    if (S_ISREG(st.st_mode)) {
        if (st.st_size > file.size) {
            file.size = st.st_size;
            file.path = calloc(1, 1024);
            strcpy(file.path, path);
        }
    } else {
        // is dir
        DIR *dir = opendir(path);
        struct dirent *ent = NULL;
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0) {
                continue;
            }
            if (strcmp(ent->d_name, "..") == 0) {
                continue;
            }

            char *next_path = malloc(1024);
            sprintf(next_path, "%s/%s", path, ent->d_name);
            dfs(next_path);
            free(next_path);
        }
    }
}
