#include <stdio.h>

#define X 3
#define Y 4

int main(void) {

    // &(array[x][y]) = array + x * sizeof(row) + y * sizeof(col)
    int array[X][Y];

    printf("sizeof array[2][3] = %lu\n", sizeof array[2][3]);
    printf("sizeof array[1] = %lu\n", sizeof array[1]);
    printf("sizeof array = %lu\n", sizeof array);

    printf("&array=%p\n", &array);
    for (int x = 0; x < X; x++) {
        printf("&array[%d]=%p\n", x, &array[x]);
        for (int y = 0; y < Y; y++) {
            printf("&array[%d][%d]=%p\n", x, y, &array[x][y]);
        }
    }
}
