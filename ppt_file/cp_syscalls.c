
#include <unistd.h>

#define O_RDONLY 00
#define O_WRONLY 01
#define O_CREAT  0100

// cp <file1> <file2> with syscalls and no error handling
int main(int argc, char *argv[]) {

    // system call number 2 is open, takes 3 arguments:
    //   1) address of zero-terminated string containing file pathname
    //   2) bitmap indicating whether to write, read, ... file
    //      O_WRONLY | O_CREAT == 0x41 == write to file, creating if necessary
    //   3) permissions if file will be newly created
    //      0644 == readable to everyone, writeable by owner

    long read_file_descriptor  = syscall(2, argv[1], O_RDONLY,           0);
    long write_file_descriptor = syscall(2, argv[2], O_WRONLY | O_CREAT, 0644);

    while (1) {

        // system call number 0 is read -  takes 3 arguments:
        //   1) file descriptor
        //   2) memory address to put bytes read
        //   3) maximum number of bytes read
        // returns number of bytes actually read
        char bytes[4096];
        long bytes_read = syscall(0, read_file_descriptor, bytes, 4096);

        if (bytes_read <= 0) {
            break;
        }

        // system call number 1 is write - takes 3 arguments:
        //   1) file descriptor
        //   2) memory address to take bytes from
        //   3) number of bytes to written
        // returns number of bytes actually written

        syscall(1, write_file_descriptor, bytes, bytes_read);
    }

    return 0;
}
