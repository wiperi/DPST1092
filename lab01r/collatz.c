#include <stdio.h>
#include <stdlib.h>

void collatz(int n) {

    printf("%d\n", n);

    if (n == 1) {
        return;
    }

    if (n % 2 == 0) {
        collatz(n / 2);
    } else {
        collatz(3 * n + 1);
    }
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		return 0;
	}

	collatz(atoi(argv[1]));
	
    return EXIT_SUCCESS;
}
