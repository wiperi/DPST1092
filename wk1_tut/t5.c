#include <stdio.h>

void print_array(int nums[], int len, int i) {
    
    if (i == len) {
        return;
    }

    printf("%d\n", nums[i]);

    print_array(nums, len, i + 1);
}

int main(int argc, char *argv[], char *envp[]) {

    print_array(NULL, 3, 0);
    
}