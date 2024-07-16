#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "polymipsism.h"
#include "provided.h"


object make_object(void *data, size_t fn_capacity) {
    object obj = bumpalo(object_size(fn_capacity));

    * obj_data(obj)     = data;
    * obj_capacity(obj) = fn_capacity;
    * obj_len(obj)      = 0;

    return obj;
}

object obj_define(object obj, char *fn_name, void *(*fn_ptr)(void *)) {
    size_t fn_capacity = * obj_capacity(obj);
    size_t fn_len      = * obj_len(obj);

    if (fn_len >= fn_capacity) {
        printf("error: tried to add fn to full object\n");
        exit(1);
    }

    * obj_nth_fn_name(obj, fn_len) = fn_name;
    * obj_nth_fn_ptr(obj, fn_len)  = fn_ptr;
    * obj_len(obj)                 = fn_len + 1;

    return obj;
}

void *obj_call(object obj, char *fn) {
    size_t len = * obj_len(obj);
    for (size_t i = 0; i < len; i++) {
        if (streq(* obj_nth_fn_name(obj, i), fn)) {
            void *(*fn_ptr)(void *) = * obj_nth_fn_ptr(obj, i);

            return fn_ptr(* obj_data(obj));
        }
    }

    printf("error: could not find function\n");
    exit(1);
}
