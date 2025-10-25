
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child: replace this process with the "date" command
        execlp("date", "date", (char *)NULL);
        // If execlp returns, it's an error
        perror("execlp");
        exit(1);
    } else {
        // Parent: wait for the child to finish before printing
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        if (WIFEXITED(status)) {
            printf("Child finished with exit status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        } else {
            printf("Child finished abnormally\n");
        }
    }

    return 0;
}
