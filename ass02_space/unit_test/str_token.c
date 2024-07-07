#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    

    char path[] = "first/ /";

    char* res = strtok(path, "/");

    for (int i = 0; i < 100; i++)
    {
        printf("%s\n", res);
        res = strtok(NULL, "/");
        if (!res) {
            break;
        }
    }
    
}