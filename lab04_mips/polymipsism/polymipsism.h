#include <stdlib.h>

typedef void *object;


// for you to complete:
object  make_object    (void *data, size_t fn_capacity);
object  obj_define     (object obj, char *fn_name, void *(*fn_ptr)(void *));
void *  obj_call       (object obj, char *fn);
