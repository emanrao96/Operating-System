// exec_top.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // Child: replace this process with interactive top
        execlp("top", "top", (char *)NULL);
        // If execlp returns, it failed
        perror("execlp failed");
        return 1;
    } else {
        // Parent: print child PID then wait for child to finish
        printf("Parent: spawned child with PID %d\n", pid);
        printf("Parent: now waiting for child (top) to finish. Open another terminal to find and kill the child PID.\n");
        int status = 0;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Parent: child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent: child killed by signal %d\n", WTERMSIG(status));
        } else {
            printf("Parent: child ended abnormally\n");
        }
    }
    return 0;
}