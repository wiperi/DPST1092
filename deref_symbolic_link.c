#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define NEW_FOLDER "new_folder"

// Function to copy the content of a file
void copy_file(const char *source, const char *destination) {
    char buffer[1024];
    size_t bytes;

    FILE *src = fopen(source, "r");
    if (!src) {
        perror("Failed to open source file");
        return;
    }

    FILE *dest = fopen(destination, "w");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(src);
        return;
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
}

// Function to check if the entry is a symbolic link
int is_symlink(const char *path) {
    struct stat path_stat;
    if (lstat(path, &path_stat) != 0) {
        perror("Failed to get file status");
        return 0;
    }
    return S_ISLNK(path_stat.st_mode);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[1];
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("Failed to open directory");
        return 1;
    }

    struct dirent *entry;
    char new_folder_path[1024];

    snprintf(new_folder_path, sizeof(new_folder_path), "%s/%s", dir_path, NEW_FOLDER);

    // Create new folder if it doesn't exist
    if (mkdir(new_folder_path, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create new folder");
        closedir(dir);
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_LNK) {
            char source_path[1024];
            char destination_path[1024];

            snprintf(source_path, sizeof(source_path), "%s/%s", dir_path, entry->d_name);
            snprintf(destination_path, sizeof(destination_path), "%s/%s", new_folder_path, entry->d_name);

            // Copy the content of the symbolic link to the new folder
            copy_file(source_path, destination_path);
            remove(source_path);
        }
    }

    closedir(dir);
    return 0;
}
