#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    
}


int sumTo(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sumTo(n - 1);
}