#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        char* file_path = argv[i];

        struct stat st;
        if (stat(file_path, &st)) {
            
        }
    }
    
    return EXIT_SUCCESS;
}
