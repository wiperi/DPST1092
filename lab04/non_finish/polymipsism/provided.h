#include <stdlib.h>

typedef void *object;

// provided:
size_t  object_size    (size_t fn_capacity);
void ** obj_data       (object obj);
size_t *obj_capacity   (object obj);
size_t *obj_len        (object obj);
char ** obj_nth_fn_name(object obj, size_t n);
void ** obj_nth_fn_ptr (object obj, size_t n);
int     streq          (char *str1, char *str2);
void *  bumpalo        (size_t bytes);
