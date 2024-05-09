#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    char* argv[] = {"gcc", "hello.c", "-o", "hello_executable", NULL};
    posix_spawn_file_actions_t actions;

    // 初始化文件操作对象
    posix_spawn_file_actions_init(&actions);

    // 设置标准输出到父进程的标准输出
    posix_spawn_file_actions_addopen(&actions, STDOUT_FILENO, "/dev/stdout", O_WRONLY, 0);

    // 创建子进程
    if (posix_spawn(&pid, "/usr/bin/gcc", &actions, NULL, argv, NULL) == 0) {
        // 等待子进程结束
        waitpid(pid, NULL, 0);
    } else {
        printf("Error: Failed to spawn child process\n");
    }

    // 销毁文件操作对象
    posix_spawn_file_actions_destroy(&actions);

    return 0;
}
