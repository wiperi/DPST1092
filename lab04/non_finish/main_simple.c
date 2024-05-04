#include <stdio.h>
#include "polymipsism.h"
#include "provided.h"

void *add_5(void *data);
void *get_doubled(void *data);

int number = 0;

int main(void) {
    object obj = make_object(&number, 2);

    obj_define(obj, "add_5", add_5);
    obj_define(obj, "get_doubled", get_doubled);

    obj_call(obj, "add_5");
    int doubled = * (int *) obj_call(obj, "get_doubled");

    printf("%d\n", doubled);
    return 0;
}

void *add_5(void *data) {
    int *value = (int *) data;
    *value += 5;

    return NULL;
}

void *get_doubled(void *data) {
    int *doubled = bumpalo(sizeof(int));
    *doubled = * (int *) data * 2;

    return doubled;
}
