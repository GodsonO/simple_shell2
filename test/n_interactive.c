#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork first child process
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 1;
    } else if (pid1 == 0) {
        // Child process 1 (echo)
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close write end

        // Execute first command
        execlp("echo", "echo", "ls", NULL);
        perror("execlp");
        return 1;
    }

    // Fork second child process
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return 1;
    } else if (pid2 == 0) {
        // Child process 2 (shell)
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[0]); // Close read end

	close(STDOUT_FILENO);
        // Execute second command
        char* args[] = {"/home/vagrant/simple_shell/test/shell", NULL}; // Replace "./shell" with the actual path to your shell executable
        execvp(args[0], args);
        perror("execvp");
        return 1;
    }

    // Close unused file descriptors in the parent process
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
