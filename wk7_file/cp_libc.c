
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// cp <file1> <file2> implemented with libc and no error handling
int main(int argc, char *argv[]) {

    // open takes 3 arguments:
    //   1) address of zero-terminated string containing pathname of file to open
    //   2) bitmap indicating whether to write, read, ... file
    //   3) permissions if file will be newly created
    //      0644 == readable to everyone, writeable by owner
    int read_file_descriptor = open(argv[1], O_RDONLY);
    int write_file_descriptor = open(argv[2], O_WRONLY | O_CREAT, 0644);

    while (1) {

        // read takes 3 arguments:
        //   1) file descriptor
        //   2) memory address to put bytes read
        //   3) maximum number of bytes read
        // returns number of bytes actually read

        char bytes[4096];
        ssize_t bytes_read = read(read_file_descriptor, bytes, 4096);
        if (bytes_read <= 0) {
            break;
        }

        // write takes 3 arguments:
        //   1) file descriptor
        //   2) memory address to take bytes from
        //   3) number of bytes to written
        // returns number of bytes actually written

        write(write_file_descriptor, bytes, bytes_read);
    }

    // good practice to close file descriptions as soon as finished using them
    // not necessary needed here as program about to exit
    close(read_file_descriptor);
    close(write_file_descriptor);

    return 0;
}
