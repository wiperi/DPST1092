// hello world implemented with libc

#include <unistd.h>

int main(void) {
    char bytes[13] = "Hello, Zac!\n";

    // write takes 3 arguments:
    //   1) file descriptor, 1 == stdout
    //   2) memory address of first byte to write
    //   3) number of bytes to write

    write(1, bytes, 12); // prints Hello, Zac! on stdout

    return 0;
}
