// cp <file1> <file2>
// implemented with libc and *zero* error handling

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    // copy bytes one at a time from  pathname passed as
    // command-line argument 1 to pathname given as argument 2
    int read_file_descriptor = open(argv[1], O_RDONLY);
    int write_file_descriptor = open(argv[2], O_WRONLY | O_CREAT, 0644);
    while (1) {
        char bytes[1];
        ssize_t bytes_read = read(read_file_descriptor, bytes, 1);
        if (bytes_read <= 0) {
            break;
        }
        write(write_file_descriptor, bytes, 1);
    }

    return 0;
}
