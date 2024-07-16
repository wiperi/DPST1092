#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <errno.h>

void print_permissions(mode_t mode) {
    printf("%c", (S_ISDIR(mode)) ? 'd' : '-');
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

void print_file_info(const char *pathname) {
    struct stat file_stat;
    if (lstat(pathname, &file_stat) == -1) {
        perror(pathname);
        return;
    }

    print_permissions(file_stat.st_mode);
    printf(" %lu", file_stat.st_nlink);

    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);

    printf(" %s", pwd ? pwd->pw_name : "UNKNOWN");
    printf(" %s", grp ? grp->gr_name : "UNKNOWN");
    printf(" %5ld", (long)file_stat.st_size);

    char timebuf[80];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %e %H:%M", tm_info);
    printf(" %s %s\n", timebuf, pathname);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // No arguments, use current directory
        print_file_info(".");
    } else {
        for (int i = 1; i < argc; i++) {
            print_file_info(argv[i]);
        }
    }

    return 0;
}
