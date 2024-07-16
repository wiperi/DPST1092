#include <stdio.h>

int ackermann(int, int);

int main(void) {
    int m, n;

    printf("Enter m: ");
    scanf("%d", &m);

    printf("Enter n: ");
    scanf("%d", &n);

    int f = ackermann(m, n);

    printf("Ackermann(%d, %d) = %d\n", m, n, f);

    return 0;
}

int ackermann(int m, int n) {

    printf("%d %d\n", m, n);
    
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}
