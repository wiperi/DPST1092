#include <stdio.h>
#include "polymipsism.h"
#include "provided.h"

object make_animal(char *name, void *(*fn_ptr)(void *));

void *duck_speak(void *);
void *dog_speak(void *);
void *cat_speak(void *);

int main(void) {
    object duck = make_animal("Daffy",     duck_speak);
    object dog  = make_animal("Clifford",  dog_speak);
    object cat  = make_animal("Scruffles", cat_speak);

    obj_call(duck, "speak");
    obj_call(dog,  "speak");
    obj_call(cat,  "speak");

    return 0;
}

object make_animal(char *name, void *(*fn_ptr)(void *)) {
    object obj = make_object(name, 1);
    obj_define(obj, "speak", fn_ptr);

    return obj;
}

void *duck_speak(void *data) {
    printf("%s says quack!\n", (char *) data);
    return NULL;
}

void *dog_speak(void *data) {
    printf("%s says woof!\n", (char *) data);
    return NULL;
}

void *cat_speak(void *data) {
    printf("%s says meow!\n", (char *) data);
    return NULL;
}
