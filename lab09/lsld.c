#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void print_file_permissions(struct stat s) {
    // is dir ?
    if ((s.st_mode & __S_IFDIR) == __S_IFDIR) {
        printf("d");
    } else {
        printf("-");
    }

    // Owner Group Others
    if ((s.st_mode & S_IRUSR) == S_IRUSR)
        printf("r");
    else
        printf("-");
    if ((s.st_mode & S_IWUSR) == S_IWUSR)
        printf("w");
    else
        printf("-");
    if ((s.st_mode & S_IXUSR) == S_IXUSR)
        printf("x");
    else
        printf("-");
    if ((s.st_mode & S_IRGRP) == S_IRGRP)
        printf("r");
    else
        printf("-");
    if ((s.st_mode & S_IWGRP) == S_IWGRP)
        printf("w");
    else
        printf("-");
    if ((s.st_mode & S_IXGRP) == S_IXGRP)
        printf("x");
    else
        printf("-");
    if ((s.st_mode & S_IROTH) == S_IROTH)
        printf("r");
    else
        printf("-");
    if ((s.st_mode & S_IWOTH) == S_IWOTH)
        printf("w");
    else
        printf("-");
    if ((s.st_mode & S_IXOTH) == S_IXOTH)
        printf("x");
    else
        printf("-");
}

int main(int argc, char* argv[], char* envp[]) {

    struct stat st;

    for (int i = 1; i < argc; i++) {

        char* path = argv[i];

        if (stat(path, &st) == -1) {
            // get state
            perror(path);
        }

        print_file_permissions(st);
        printf(" %lu", (unsigned long)st.st_nlink);
        printf(" %s", getpwuid(st.st_uid)->pw_name); // 文件所有者用户名
        printf(" %s", getgrgid(st.st_gid)->gr_name); // 文件所属组名
        printf(" %ld", (long)st.st_size);            // 文件大小

        char date_string[80];
        strftime(date_string, sizeof(date_string), "%b %e %H:%M", localtime(&st.st_mtime));
        printf(" %s", date_string);
        // printf(" %s", ctime(&st.st_mtime)); // 最后修改时间


        printf(" %s\n", path);              // 文件名
    }
}