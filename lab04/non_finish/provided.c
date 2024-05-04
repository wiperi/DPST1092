#include <stdlib.h>
#include <unistd.h>
#include "provided.h"

//
// THE FOLLOWING FUNCTIONS ARE PROVIDED FOR YOU
//

size_t object_size(size_t fn_capacity) {
    return sizeof(void *) + 2 * sizeof(size_t) + fn_capacity * (sizeof(char *) + sizeof(void *));
}

void **obj_data(object obj) {
    return (void **) obj;
}

size_t *obj_capacity(object obj) {
    return (size_t *) (obj + sizeof(void *));
}

size_t *obj_len(object obj) {
    return (size_t *) (obj + sizeof(void *) + sizeof(size_t));
}

char **obj_nth_fn_name(object obj, size_t n) {
    return (char **) (obj + sizeof(void *) + sizeof(size_t) + sizeof(size_t) + n * (sizeof(char *) + sizeof(void *)));
}

void **obj_nth_fn_ptr(object obj, size_t n) {
    return (void **) (obj + sizeof(void *) + sizeof(size_t) + sizeof(size_t) + n * (sizeof(char *) + sizeof(void *)) + sizeof(char *));
}

int streq(char *str1, char *str2) {
    if (!*str1) {
        return !*str2;
    }

    if (*str1 != *str2) {
        return 0;
    }

    return streq(str1 + 1, str2 + 1);
}

void *bumpalo(size_t bytes) {
    void *ptr = sbrk(0);
    sbrk(bytes);

    return ptr;
}
