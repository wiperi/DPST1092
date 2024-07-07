#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Node {
    char* path_name;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* head;
    Node* tail;
} Queue;

int queue_is_empty(Queue* q) {
    return q->head == NULL;
}

Node* new_Node(const char* path_name) {
    Node* new_Node = malloc(sizeof(Node));
    new_Node->path_name = strdup(path_name);
    new_Node->next = NULL;
    return new_Node;
}

void enqueue(Queue* q, Node* node) {

    if (queue_is_empty(q)) {
        q->head = node;
        q->tail = node;
        return;
    }

    q->tail->next = node;
    q->tail = q->tail->next;
}

char* dequeue(Queue* q) {

    if (queue_is_empty(q)) {
        return NULL;
    }

    Node* prev_head = q->head;
    char* path_name = strdup(q->head->path_name);

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(prev_head->path_name);
    free(prev_head);

    return path_name;
}

int bfs(const char* path_name) {

    Queue q = {NULL, NULL};
    enqueue(&q, new_Node(path_name));

    while (!queue_is_empty(&q)) {
        char* cur_path = dequeue(&q);
        printf("%s\n", cur_path);

        DIR* dir = opendir(cur_path);
        if (dir == NULL) {
            continue;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", cur_path, entry->d_name);

            struct stat st;
            if (stat(new_path, &st) == -1) {
                perror("stat");
                continue;
            }

            if (S_ISDIR(st.st_mode)) {
                enqueue(&q, new_Node(new_path));
            } else if (S_ISREG(st.st_mode)) {
                printf("%s\n", new_path);
            }
        }

        closedir(dir);
    }
}

int ls_dir(const char* path_name) {

    Queue q = {NULL, NULL};
    enqueue(&q, new_Node(path_name));

    while (!queue_is_empty(&q)) {
        char* cur_path = dequeue(&q);
        printf("%s\n", cur_path);

        DIR* dir = opendir(cur_path);
        if (dir == NULL) {
            continue;
        }

        struct dirent** entry_list;
        int n_entries = scandir(cur_path, &entry_list, NULL, alphasort);
        if (n_entries == -1) {
            perror("scandir");
            continue;
        }

        for (int i = 0; i < n_entries; i++) {

            struct dirent* entry = entry_list[i];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", cur_path, entry->d_name);

            struct stat st;
            if (stat(new_path, &st) == -1) {
                perror("stat");
                continue;
            }

            if (S_ISDIR(st.st_mode)) {
                enqueue(&q, new_Node(new_path));
            } else if (S_ISREG(st.st_mode)) {
                printf("%s\n", new_path);
            }
        }

        closedir(dir);
    }
}

int main(int argc, char* argv[]) {

    ls_dir("tmp");

    return 0;
}
