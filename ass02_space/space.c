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

void encode_7bit(FILE* from, FILE* to, uint8_t* hash, uint64_t content_len);
void decode_7bit(char* content, uint64_t content_len, FILE* to);
uint8_t cut_head(uint8_t ch, int head_len);
uint8_t cut_body(uint8_t ch, int body_len);
void encode_6bit(FILE* from, FILE* to, uint8_t* hash, uint64_t content_len);
void decode_6bit(char* content, uint64_t content_len, FILE* to);

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

        // calculate star content len (after compression, the length of content[])
        uint64_t star_content_len = 0;
        if (star_format == STAR_FMT_6) {
            if (((content_len * 6) % 8) == 0) {
                star_content_len = ((content_len * 6) / 8);
            } else {
                star_content_len = ((content_len * 6) / 8) + 1;
            }
        } else if (star_format == STAR_FMT_7) {
            if (((content_len * 7) % 8) == 0) {
                star_content_len = ((content_len * 7) / 8);
            } else {
                star_content_len = ((content_len * 7) / 8) + 1;
            }
        } else {
            star_content_len = content_len;
        }

        // read content
        char content[star_content_len + 1];
        for (int i = 0; i < star_content_len; i++) {
            ch = hash_getc(file, &hash);

            content[i] = ch;
        }
        content[star_content_len] = '\0';
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

        // extract stars
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
                if (star_format == STAR_FMT_7) {   
                    decode_7bit(content, content_len, new_file);
                } else if (star_format == STAR_FMT_6) {
                    decode_6bit(content, content_len, new_file);
                } else {
                    if (fwrite(content, 1, content_len, new_file) != content_len) {
                        perror(path_name);
                        exit(1);
                    }
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

    // extracting jobs done in check_galaxy()

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

    
    // waitlist records stars to be added to galaxy
    Queue waitlist = {NULL, NULL};

    // add all pathnames to waitlist
    for (int i = 0; i < n_pathnames; i++) {
        sub_path(pathnames[i], &waitlist);
        bfs_directory(pathnames[i], &waitlist);
    }

    // open galaxy
    FILE* galaxy = fopen(galaxy_pathname, append ? "a" : "w");
    if (galaxy == NULL) {
        perror(galaxy_pathname);
        exit(1);
    }

    // empty waitlist
    while (!queue_is_empty(&waitlist)) {

        char* star_path_name = dequeue(&waitlist);

        if (strstr(star_path_name, "..")) {
            fprintf(stderr, "error: Can not add paths containing '..' to galaxy\n");
            exit(1);
        }

        // create star
        FILE* star = fopen(star_path_name, "r");
        if (star == NULL) {
            perror(star_path_name);
            exit(1);
        }

        printf("Adding: %s\n", star_path_name);

        // init star hash
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
            encode_7bit(star, galaxy, &hash, content_len);
        } else if (format == STAR_FMT_6) {
            encode_6bit(star, galaxy, &hash, content_len);
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

/**
 * Read a character from a file and update the hash value.
 * 
 * @param file The file to read from.
 * @param hash The hash value to update.
 * @return The character read from the file.
 */
int hash_getc(FILE* file, uint8_t* hash) {
    int ch = fgetc(file);
    if (ch == EOF) {
        fprintf(stderr, "error: unexpected EOF in galaxy\n");
        exit(1);
    }
    *hash = galaxy_hash(*hash, ch);
    return ch;
}

/**
 * Write a character to a file and update the hash value.
 * 
 * @param file The file to write to.
 * @param hash The hash value to update.
 * @param ch The character to write to the file.
 * @return The character written to the file.
 */
int hash_putc(FILE* file, uint8_t* hash, int ch) {
    if (fputc(ch, file) == EOF) {
        perror("fputc");
        exit(1);
    }
    *hash = galaxy_hash(*hash, ch);
    return ch;
}

/**
 * Convert a little-endian byte sequence to an unsigned integer.
 * 
 * @param file The file to read from.
 * @param n_bytes The number of bytes to read.
 * @param hash The hash value to update.
 * @return The unsigned integer represented by the byte sequence.
 */
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

/**
 * Convert an unsigned integer to a little-endian byte sequence and write it to a file.
 * 
 * @param file The file to write to.
 * @param n_bytes The number of bytes to write.
 * @param num The unsigned integer to write.
 * @param hash The hash value to update.
 * @return The remaining value of the unsigned integer.
 */
uint64_t uint_to_little_endian(FILE* file, int n_bytes, uint64_t num, uint8_t* hash) {

    assert(n_bytes <= 8);

    for (int i = 0; i < n_bytes; i++) {
        hash_putc(file, hash, num & 0xff);
        num >>= 8;
    }

    return num;
}

/**
 * Modify the permissions of a file or directory.
 * 
 * @param path_name The path name of the file or directory.
 * @param permissions The new permissions to set.
 * @return 0 if successful, -1 otherwise.
 */
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

/**
 * Check if a queue is empty.
 * 
 * @param q The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int queue_is_empty(Queue* q) {
    return q->head == NULL;
}

/**
 * Create a new node. The node holds a copy of the given string in headp memory.
 * 
 * @param path_name The path name of the node.
 * @return The new node.
 */
Node* new_Node(const char* path_name) {
    Node* new_Node = malloc(sizeof(Node));
    new_Node->path_name = strdup(path_name);
    new_Node->next = NULL;
    return new_Node;
}

/**
 * Add a node to the end of a queue.
 * 
 * @param q The queue to add the node to.
 * @param node The node to add.
 */
void enqueue(Queue* q, Node* node) {

    if (queue_is_empty(q)) {
        q->head = node;
        q->tail = node;
        return;
    }

    q->tail->next = node;
    q->tail = q->tail->next;
}

/**
 * Remove and return the head of a queue.
 * 
 * @param q The queue to remove the head from.
 * @return The path name of the head node, stored in heap memory.
 */
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

/**
 * Breadth-first search a directory (in alphabetically ascending order) and add all files and subdirectories to a queue.
 * 
 * @param path_name The path name of the directory.
 * @param waitlist The queue to add the files and subdirectories to.
 */
void bfs_directory(const char* path_name, Queue* waitlist) {

    Queue q = {NULL, NULL};
    enqueue(&q, new_Node(path_name));

    while (!queue_is_empty(&q)) {
        char* cur_path = dequeue(&q);
        enqueue(waitlist, new_Node(cur_path));

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

            // ignore . and ..
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
                enqueue(waitlist, new_Node(new_path));
            }
        }

        closedir(dir);
    }
}

/**
 * Add all sub paths of a path name to a queue.
 * 
 * Subpath example: /a/b/c -> /a, /a/b
 * 
 * @param path_name The path name to add sub paths from.
 * @param waitlist The queue to add the sub paths to.
 */
void sub_path(const char* path_name, Queue* waitlist) {

    for (size_t i = 0; i < strlen(path_name); i++) {
        if (path_name[i] == '/') {
            // new sub path
            char sub_path[i + 1];
            for (size_t j = 0; j < i; j++) {
                sub_path[j] = path_name[j];
            }
            sub_path[i] = '\0';
            enqueue(waitlist, new_Node(sub_path));
        }
    }
}

/**
 * Encode a file in 7-bit format and write the encoded data to a file.
 * 
 * @param from The file to read from.
 * @param to The file to write to.
 * @param hash The hash value to update.
 * @param content_len The length of the content to encode.
 */
void encode_7bit(FILE* from, FILE* to, uint8_t* hash, uint64_t content_len) {

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
                    fprintf(stderr, "error: byte 0x%x can not be represented in 7-bit format\n", src_byte);
                    exit(1);
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
}

void encode_6bit(FILE* from, FILE* to, uint8_t* hash, uint64_t content_len) {

    uint64_t bit_buffer = 0;
    int bit_count = 0;
    int n_encoded = 0;

    while (1) {
        int byte_read = fgetc(from);
        if (byte_read == EOF) {
            break;
        }
        
        uint8_t eight_bit = (uint8_t) byte_read;
        int six_bit = galaxy_to_6_bit(eight_bit);
        if (six_bit == -1) {
            fprintf(stderr, "error: byte 0x%x can not be represented in 6-bit format\n", byte_read);
            exit(1);
        }

        // valid six bit value add to buffer
        bit_buffer = (bit_buffer << 6) | (six_bit & 0x3f);
        bit_count += 6;

        // shrink buffer?
        while (bit_count >= 8) {
            bit_count -= 8;
            hash_putc(to, hash, ((bit_buffer >> bit_count) & 0xff));
            n_encoded++;
        }
    }

    if (bit_count > 0) {
        hash_putc(to, hash, (bit_buffer << (8 - bit_count)) & 0xff);
    }
}

void decode_6bit(char* content, uint64_t content_len, FILE* to) {

    uint64_t bit_buffer = 0;
    int bit_count = 0;
    int n_decoded = 0;

    for (uint64_t i = 0; i < content_len; i++)
    {
        uint8_t byte_read = content[i];

        // add 8 bit to buffer
        bit_buffer = (bit_buffer << 8) | byte_read;
        bit_count += 8;

        // shrink buffer?
        while (bit_count >= 6) {
            bit_count -= 6;
            uint8_t six_bit = (bit_buffer >> bit_count) & 0x3f;

            int eight_bit = galaxy_from_6_bit(six_bit);
            if (eight_bit == -1) {
                fprintf(stderr, "error: invalid 6 bit value 0x%x\n", six_bit);
                exit(1);
            }
            fputc(eight_bit, to);
            n_decoded++;
            if (n_decoded == content_len) {
                return;
            }
        }
    }
}


/**
 * Cuts the head of a given character by a specified length.
 *
 * @param ch The character to cut the head from.
 * @param head_len The length of the head to cut.
 * @return The resulting character after cutting the head.
 */
uint8_t cut_head(uint8_t ch, int head_len) {
    return (ch >> (8 - head_len));
}

/**
 * Cuts the body of a character based on the specified length.
 *
 * @param ch The character to cut the body from.
 * @param body_len The length of the body to cut.
 * @return The resulting character after cutting the body.
 */
uint8_t cut_body(uint8_t ch, int body_len) {
    uint32_t mask = (1 << body_len) - 1;
    return (ch & mask) << (7 - body_len);
}

/**
 * Decodes a 7-bit encoded content and writes the decoded data to a file.
 *
 * @param content The 7-bit encoded content to be decoded.
 * @param content_len The length of the content.
 * @param to The file pointer to write the decoded data to.
 */
void decode_7bit(char* content, uint64_t content_len, FILE* to) {

    /**
     * Divide each byte into two parts: head and body.
     * 
     * Head will be assembled with previous body to form a 7-bit sequence.
     * 
     * Body will be assembled with next head to form a 7-bit sequence.
     */

    int head = 0;
    int body = 0;
    int head_len = 7;
    int n_decoded = 0;
    int i = 0;

    while (1) {

        uint8_t ch = content[i++];
        int body_len = 8 - head_len;

        head = cut_head(ch, head_len);

        fputc(head | body, to);
        n_decoded++;
        if (n_decoded == content_len) {
            return;
        }

        body = cut_body(ch, body_len);

        if (body_len == 7) {
            fputc(ch & 0x7f, to);
            n_decoded++;
            if (n_decoded == content_len) {
                return;
            }

            head_len = 7;
            head = 0;
            body = 0;
        } else {
            head_len--;
        }
    }
}