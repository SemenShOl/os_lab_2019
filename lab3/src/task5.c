#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execl("./sequential_min_max", "./sequential_min_max", "3", "3", NULL);

        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child proccess ended with code: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child proccess ended with error\n");
        }
    }

    printf("Parent proccess ended with code: 0\n");
    return 0;
}