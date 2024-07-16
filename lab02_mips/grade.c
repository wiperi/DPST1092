// read a mark and print the corresponding UNSW grade

#include <stdio.h>

int main(void) {
    int mark;

    printf("Enter a mark: ");
    scanf("%d", &mark);

    if (mark < 50) {
        printf("FL\n");
    } else if (mark < 65) {
        printf("PS\n");
    } else if (mark < 75) {
        printf("CR\n");
    } else if (mark < 85) {
        printf("DN\n");
    } else {
        printf("HD\n");
    }

    return 0;
}

int simplified(void) {
    int mark;
    if (mark < 50)
        goto fl;
    if (mark < 65)
        goto PS;
    if (mark < 75)
        goto CR;
    if (mark < 85)
        goto DN;
    goto HD;
    
fl:
    printf("FL\n");
    goto end;
PS:
    printf("PS\n");
    goto end;
CR:
    printf("CR\n");
    goto end;
DN:
    printf("DN\n");
    goto end;
HD:
    printf("HD\n");
    goto end;

end:
    return;
}
