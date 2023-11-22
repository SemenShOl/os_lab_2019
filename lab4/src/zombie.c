#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// parent proccess
int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) { // child proccess
        printf("Child process is running\n");
        sleep(10);
        printf("Child process is done\n");
        exit(0); 
    } else if (child_pid > 0) { // родительский
        printf("Parent process is waiting for the child...\n");
        wait(NULL);
        printf("Parent process is done\n");
    } else {
        perror("fork");
        return 1; 
    }

    return 0;
}