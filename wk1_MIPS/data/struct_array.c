// simple example of accessing struct within array within struct

#include <stdio.h>

#define MAX_POLYGON 6

struct point {
    int x;
    int y;
};

struct polygon {
    int degree;
    struct point vertices[MAX_POLYGON]; // C also allows variable size array here
};

void print_last_vertex(struct polygon* p);

struct polygon triangle = {3, {{0, 0}, {3, 0}, {0, 4}}};

int main(void) {
    print_last_vertex(&triangle); // prints 0,4
    return 0;
}

void print_last_vertex(struct polygon* p) {
    printf("%d", p->vertices[p->degree - 1].x);
    putchar(',');
    printf("%d", p->vertices[p->degree - 1].y);
    putchar('\n');
}
