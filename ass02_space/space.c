////////////////////////////////////////////////////////////////////////
// DPST1092 --- Assignment 2: `space', a simple file archiver
//
//
// Written by Tianyang Chen (z5567323) on 3/July/2024.
//
// 2024-03-08   v1.1    Team DPST1092

#include <assert.h>
#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "space.h"

// ADD ANY extra #defines HERE

#define DEBUG_MODE 0
#define DEBUG_MESSAGE_OFFSET_STRING 20
#define DEBUG_MESSAGE_OFFSET_OTHER 10

// ADD YOUR FUNCTION PROTOTYPES (AND STRUCTS IF ANY) HERE

uint8_t check_galaxy_mode = 0;
#define DEFAULT 0
#define SILENCE 0x1
#define LIST_STARS 0x2
#define LIST_STARS_VERBOSE 0x4
#define EXTRACT_STARS 0x8
#define CHECK_GALAXY_MODE(M) (check_galaxy_mode & M)

// STRUCTS

typedef struct Node {
    char* path_name;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* head;
    Node* tail;
} Queue;

// FUNCTION PROTOTYPES

int hash_getc(FILE* file, uint8_t* hash);
int hash_putc(FILE* file, uint8_t* hash, int ch);
uint64_t little_endian_to_uint(FILE* file, int n_bytes, uint8_t* hash);
uint64_t uint_to_little_endian(FILE* file, int n_bytes, uint64_t num, uint8_t* hash);
int modify_file_permissions(const char* path_name, const char* permissions);

int queue_is_empty(Queue* q);
Node* new_Node(const char* path_name);
void enqueue(Queue* q, Node* node);
char* dequeue(Queue* q);

void bfs_directory(const char* path_name, Queue* awaiting_queue);
void sub_path(const char* path_name, Queue* awaiting_queue);

void encode(FILE* from, FILE* to, uint8_t* hash, uint64_t content_len);

// print the files & directories stored in galaxy_pathname (subset 0)
//
// if long_listing is non-zero then file/directory permissions, formats & sizes
// are also printed (subset 0)
//
// It is not necessary to check the hashes or magic numbers of stars in subset
// 0. Subset 0 tests will only use valid stars.

void list_galaxy(char* galaxy_pathname, int long_listing) {

    check_galaxy_mode |= SILENCE;
    if (long_listing) {
        check_galaxy_mode |= LIST_STARS_VERBOSE;
    } else {
        check_galaxy_mode |= LIST_STARS;
    }
    check_galaxy(galaxy_pathname);
    check_galaxy_mode = DEFAULT;
}

// check the files & directories stored in galaxy_pathname (subset 1)
//
// prints the files & directories stored in galaxy_pathname with a message
// either, indicating the hash byte is correct, or indicating the hash byte
// is incorrect, what the incorrect value is and the correct value would be

void check_galaxy(char* galaxy_pathname) {

    /**
     * pseudo:
     * 
     * open file
     * 
     * check if file end
     * check magic
     * check format
     * check permissions
     * read path len
     * check path name
     * read content len
     * check content
     * check hash
     */

    FILE* file = fopen(galaxy_pathname, "r");
    if (file == NULL) {
        fprintf(stderr, "%s: No such file or directory", galaxy_pathname);
        exit(1);
    }

    int ch;

    while (1) {
        // check if file ends
        ch = fgetc(file);
        fseek(file, -1, SEEK_CUR);
        if (ch == EOF) {
            return;
        }

        uint8_t hash = 0;

        // check magic
        ch = hash_getc(file, &hash);
        if (ch != 'c') {
            fprintf(stderr,
                    "error: incorrect first star byte: 0x%x should be 0x63\n", ch);
            exit(1);
        }
        if (DEBUG_MODE) printf("%-*s %*c\n", DEBUG_MESSAGE_OFFSET_STRING, "magic:", DEBUG_MESSAGE_OFFSET_OTHER, ch);

        // check star format
        ch = hash_getc(file, &hash);
        switch (ch) {
        case '8':
        case '7':
        case '6':
            break;
        default:
            fprintf(stderr, "error: unknown star format: 0x%x\n", ch);
            exit(1);
            break;
        }
        char star_format = ch;
        if (DEBUG_MODE) printf("%-*s %*c\n", DEBUG_MESSAGE_OFFSET_STRING, "star format:", DEBUG_MESSAGE_OFFSET_OTHER, ch);

        // check permissions
        int permissions_invalid = 0;
        char permissions[11];
        for (int i = 0; i < 10; i++) {
            ch = hash_getc(file, &hash);
            permissions[i] = ch;

            if (i == 0) {
                switch (ch) {
                    case '-':
                    case 'd':
                        break;
                    default:
                        permissions_invalid = 1;
                        break;
                }
            } else {
                switch (ch) {
                    case '-':
                    case 'r':
                    case 'w':
                    case 'x':
                        break;
                    default:
                        permissions_invalid = 1;
                        break;
                }
            }
        }
        permissions[10] = '\0';
        if (permissions_invalid) {
            fprintf(stderr, "error: invalid permission string %s\n", permissions);
            exit(1);
        }
        if (DEBUG_MODE) printf("%-*s %*s\n", DEBUG_MESSAGE_OFFSET_STRING, "permisson:", DEBUG_MESSAGE_OFFSET_OTHER, permissions);

        // check pathlen
        uint64_t pathlen = little_endian_to_uint(file, 2, &hash);
        if (DEBUG_MODE) printf("%-*s %*lx\n", DEBUG_MESSAGE_OFFSET_STRING, "pathlen:", DEBUG_MESSAGE_OFFSET_OTHER, pathlen);

        // read path name
        char path_name[pathlen + 1];
        for (int i = 0; i < pathlen; i++) {
            ch = hash_getc(file, &hash);

            path_name[i] = ch;
        }
        path_name[pathlen] = '\0';
        if (DEBUG_MODE) printf("%-*s %*s\n", DEBUG_MESSAGE_OFFSET_STRING, "path name:", DEBUG_MESSAGE_OFFSET_OTHER, path_name);

        // read content len
        uint64_t content_len = little_endian_to_uint(file, 6, &hash);
        if (DEBUG_MODE) printf("%-*s %*lx\n", DEBUG_MESSAGE_OFFSET_STRING, "content len:", DEBUG_MESSAGE_OFFSET_OTHER, content_len);

        // check content
        char content[content_len + 1];
        for (int i = 0; i < content_len; i++) {
            ch = hash_getc(file, &hash);

            content[i] = ch;
        }
        content[content_len] = '\0';
        if (DEBUG_MODE) printf("%-*s %*s\n", DEBUG_MESSAGE_OFFSET_STRING, "content:", DEBUG_MESSAGE_OFFSET_OTHER, content);

        // check hash
        int hash_byte = fgetc(file);
        if (hash_byte == EOF) {
            fprintf(stderr, "error: unexpected EOF in galaxy\n");
            exit(1);
        }

        // print hash comparision ressult
        if (CHECK_GALAXY_MODE(SILENCE)) {
            if (hash_byte == hash) {
                ;
            } else {
                fprintf(stderr, "%s - incorrect hash 0x%x should be 0x%x\n", path_name, hash, hash_byte);
                exit(1);
            }
        } else {
            if (hash_byte == hash) {
                printf("%s - correct hash\n", path_name);
            } else {
                printf("%s - incorrect hash 0x%x should be 0x%x\n", path_name, hash, hash_byte);
            }
        }

        // list stars
        if (CHECK_GALAXY_MODE(LIST_STARS_VERBOSE)) {
            printf("%10s %2c %6ld  %s\n", permissions, star_format, content_len, path_name);
        } else if (CHECK_GALAXY_MODE(LIST_STARS)) {
            printf("%s\n", path_name);
        }

        // extract starts
        if (CHECK_GALAXY_MODE(EXTRACT_STARS)) {

            if (permissions[0] == 'd') {
                // create dir
                printf("Creating directory: %s\n", path_name);

                // create dir
                if (mkdir(path_name, 0777) == -1) {
                    perror(path_name);
                    exit(1);
                }

                // modify permissions
                if (modify_file_permissions(path_name, permissions) == -1) {
                    fprintf(stderr, "error: failed to modify permissions for %s\n", path_name);
                    exit(1);
                }

            } else {
                // create file
                printf("Extracting: %s\n", path_name);

                // create file
                FILE* new_file = fopen(path_name, "w");
                if (new_file == NULL) {
                    perror(path_name);
                    exit(1);
                }

                // write content
                if (fwrite(content, 1, content_len, new_file) != content_len) {
                    perror(path_name);
                    exit(1);
                }

                // modify permissions
                if (modify_file_permissions(path_name, permissions) == -1) {
                    fprintf(stderr, "error: failed to modify permissions for %s\n", path_name);
                    exit(1);
                }

                // close file
                fclose(new_file);
            }
        }
    }

    fclose(file);
}

// extract the files/directories stored in galaxy_pathname (subset 1 & 3)

void extract_galaxy(char* galaxy_pathname) {

    /**
     * pseudo:
     * 
     * check galaxy
     */

    check_galaxy_mode |= SILENCE;
    check_galaxy_mode |= EXTRACT_STARS;
    check_galaxy(galaxy_pathname);
    check_galaxy_mode = DEFAULT;
}

// create galaxy_pathname containing the files or directories specified in
// pathnames (subset 2 & 3)
//
// if append is zero galaxy_pathname should be over-written if it exists
// if append is non-zero galaxys should be instead appended to galaxy_pathname
//                       if it exists
//
// format specifies the galaxy format to use, it must be one STAR_FMT_6,
// STAR_FMT_7 or STAR_FMT_8

void create_galaxy(char* galaxy_pathname, int append, int format,
                   int n_pathnames, char* pathnames[n_pathnames]) {

    
    Queue awaiting_queue = {NULL, NULL};

    for (int i = 0; i < n_pathnames; i++) {
        sub_path(pathnames[i], &awaiting_queue);
        bfs_directory(pathnames[i], &awaiting_queue);
    }

    FILE* galaxy = fopen(galaxy_pathname, append ? "a" : "w");
    if (galaxy == NULL) {
        perror(galaxy_pathname);
        exit(1);
    }

    while (!queue_is_empty(&awaiting_queue)) {
        char* star_path_name = dequeue(&awaiting_queue);

        // create star

        if (strstr(star_path_name, "..")) {
            fprintf(stderr, "error: Can not add paths containing '..' to galaxy\n");
            exit(1);
        }

        FILE* star = fopen(star_path_name, "r");
        if (star == NULL) {
            perror(star_path_name);
            exit(1);
        }

        printf("Adding: %s\n", star_path_name);

        uint8_t hash = 0;

        // write magic
        hash_putc(galaxy, &hash, STAR_MAGIC);

        // write format
        hash_putc(galaxy, &hash, format);

        // write permissions
        struct stat st;
        if (stat(star_path_name, &st) == -1) {
            perror(star_path_name);
            exit(1);
        }

        char permissions[11];
        permissions[0] = S_ISDIR(st.st_mode) ? 'd' : '-';
        permissions[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
        permissions[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
        permissions[10] = '\0';
        for (int i = 0; i < 10; i++) {
            hash_putc(galaxy, &hash, permissions[i]);
        }

        // write path len
        uint64_t path_len = strlen(star_path_name);
        uint_to_little_endian(galaxy, 2, path_len, &hash);

        // write path name
        for (int i = 0; i < path_len; i++) {
            hash_putc(galaxy, &hash, star_path_name[i]);
        }

        // write content len
        uint64_t content_len = 0;
        if (S_ISDIR(st.st_mode)) {
            uint_to_little_endian(galaxy, 6, 0, &hash);
        } else {
            fseek(star, 0, SEEK_END);
            content_len = ftell(star);
            fseek(star, 0, SEEK_SET);
            uint_to_little_endian(galaxy, 6, content_len, &hash);
        }

        // write content
        if (format == STAR_FMT_7) {
            encode(star, galaxy, &hash, content_len);
        } else if (format == STAR_FMT_6) {

        } else {
            for (int i = 0; i < content_len; i++) {
                hash_putc(galaxy, &hash, fgetc(star));
            }
        }

        // write hash
        fputc(hash, galaxy);

        fclose(star);
    }
}

// ADD YOUR EXTRA FUNCTIONS HERE

int hash_getc(FILE* file, uint8_t* hash) {
    int ch = fgetc(file);
    if (ch == EOF) {
        fprintf(stderr, "error: unexpected EOF in galaxy\n");
        exit(1);
    }
    *hash = galaxy_hash(*hash, ch);
    return ch;
}

int hash_putc(FILE* file, uint8_t* hash, int ch) {
    if (fputc(ch, file) == EOF) {
        perror("fputc");
        exit(1);
    }
    *hash = galaxy_hash(*hash, ch);
    return ch;
}

uint64_t little_endian_to_uint(FILE* file, int n_bytes, uint8_t* hash) {

    assert(n_bytes <= 8);

    uint64_t res = 0;
    int ch;
    for (int i = 0; i < n_bytes; i++) {
        ch = hash_getc(file, hash);

        res |= ((uint64_t) ch << (i * 8));
    }

    return res;
}

uint64_t uint_to_little_endian(FILE* file, int n_bytes, uint64_t num, uint8_t* hash) {

    assert(n_bytes <= 8);

    for (int i = 0; i < n_bytes; i++) {
        hash_putc(file, hash, num & 0xff);
        num >>= 8;
    }

    return num;
}

int modify_file_permissions(const char* path_name, const char* permissions) {

    if (strlen(permissions) != 10) {
        fprintf(stderr, "Invalid permission string format. Expected '-rwxrwxrwx'\n");
        return -1;
    }

    struct stat st;
    if (stat(path_name, &st) != 0) {
        perror("Error getting file status");
        return -1;
    }

    // Check if the file is a directory or a regular file
    if (permissions[0] == 'd') {
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "error: %s is not a directory\n", path_name);
            return -1;
        }
    } else {
        if (!S_ISREG(st.st_mode)) {
            fprintf(stderr, "error: %s is not a regular file\n", path_name);
            return -1;
        }
    }

    // Remove all permissions
    mode_t new_mode = st.st_mode & ~(S_IRWXU | S_IRWXG | S_IRWXO);

    // User permissions
    if (permissions[1] == 'r') new_mode |= S_IRUSR;
    if (permissions[2] == 'w') new_mode |= S_IWUSR;
    if (permissions[3] == 'x') new_mode |= S_IXUSR;

    // Group permissions
    if (permissions[4] == 'r') new_mode |= S_IRGRP;
    if (permissions[5] == 'w') new_mode |= S_IWGRP;
    if (permissions[6] == 'x') new_mode |= S_IXGRP;

    // Others permissions
    if (permissions[7] == 'r') new_mode |= S_IROTH;
    if (permissions[8] == 'w') new_mode |= S_IWOTH;
    if (permissions[9] == 'x') new_mode |= S_IXOTH;

    if (chmod(path_name, new_mode) != 0) {
        perror("Error changing file permissions");
        return -1;
    }

    return 0;
}



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

void bfs_directory(const char* path_name, Queue* awaiting_queue) {

    Queue q = {NULL, NULL};
    enqueue(&q, new_Node(path_name));

    while (!queue_is_empty(&q)) {
        char* cur_path = dequeue(&q);
        enqueue(awaiting_queue, new_Node(cur_path));

        // ignore regular file
        DIR* dir = opendir(cur_path);
        if (dir == NULL) {
            continue;
        }

        // get entry list of dir
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

            char new_path[strlen(cur_path) + strlen(entry->d_name) + 2];
            snprintf(new_path, sizeof(new_path), "%s/%s", cur_path, entry->d_name);

            struct stat st;
            if (stat(new_path, &st) == -1) {
                perror("stat");
                continue;
            }

            // ignore regular file
            if (S_ISDIR(st.st_mode)) {
                enqueue(&q, new_Node(new_path));
            } else if (S_ISREG(st.st_mode)) {
                enqueue(awaiting_queue, new_Node(new_path));
            }
        }

        closedir(dir);
    }
}

void sub_path(const char* path_name, Queue* awaiting_queue) {

    for (size_t i = 0; i < strlen(path_name); i++) {
        if (path_name[i] == '/') {
            // new sub path
            char sub_path[i + 1];
            for (size_t j = 0; j < i; j++) {
                sub_path[j] = path_name[j];
            }
            sub_path[i] = '\0';
            enqueue(awaiting_queue, new_Node(sub_path));
        }
    }
}

void encode(FILE* from, FILE* to, uint8_t* hash, uint64_t content_len) {

    int encode_i = 0;
    uint8_t encoded = 0;
    int n_encoded = 0;

    while (1) {

        int src_byte = fgetc(from);
        if (src_byte == EOF) {
            if (encode_i != 0) {
                hash_putc(to, hash, encoded);
                n_encoded++;
            }
            break;
        }

        for (int i = 0; i < 8; i++) {
            unsigned bit = (src_byte >> (7 - i)) & 01;

            if (i == 0) {
                // dicard first bit
                if (bit == 1) {
                    fprintf(stderr, "error: byte 0x%x can not be represented in 6-bit format\n", src_byte);
                }
            } else {
                // append bit
                encoded |= (bit << (7 - encode_i));
                encode_i++;

                if (encode_i == 8) {
                    hash_putc(to, hash, encoded);
                    encode_i = 0;
                    encoded = 0;
                    n_encoded++;
                }
            }
        }
    }

    for (int i = n_encoded; i < content_len; i++) {
        hash_putc(to, hash, 0);
    }
}

uint8_t cut_head(uint8_t ch, int head_len) {
    return (ch >> (8 - head_len));
}

uint8_t cut_body(uint8_t ch, int body_len) {
    uint32_t mask = (1 << body_len) - 1;
    return (ch & mask) << (7 - body_len);
}

void decode(FILE* from, FILE* to, int head_len, uint8_t head, uint8_t body, uint8_t* hash) {

    int body_len = 8 - head_len;

    int ch = fgetc(from);
    if (ch == EOF) {
        return;
    }

    head = cut_head(ch, head_len);

    hash_putc(to, hash, head | body);

    body = cut_body(ch, body_len);

    if (body_len == 7) {
        hash_putc(to, hash, head | body);
        decode(from, to, 7, 0, 0);
    } else {
        decode(from, to , head_len - 1, head, body);
    }
}