#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to execute a command in non-interactive mode and capture output
char* executeCommand(const char* command);

// Function to create a pipe
int createPipe(int pipefd[2]);

// Function to fork a child process
pid_t forkChild();

// Function to redirect stdout to the write end of the pipe
void redirectStdout(int pipefd[2]);

// Function to close file descriptors
void closeFileDescriptors(int fd1, int fd2);

// Function to execute the command in the child process
void executeChildCommand(const char* command);

// Function to read command output from the pipe
ssize_t readCommandOutput(int fd, char* buffer, size_t bufferSize);

// Function to receive data from the pipe
char* receivePipeData(int pipefd[2]);

// Function to run the piped command
void runPipedCommand(const char* command);

// Main function to execute the command and print the output
void runCommand(const char* command);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s command\n", argv[0]);
        return 1;
    }

    const char* command = argv[1];
    runCommand(command);

    return 0;
}

char* executeCommand(const char* command) {
    int pipefd[2];
    char* result = NULL;

    if (createPipe(pipefd) == -1) {
        printf("Pipe creation failed\n");
        return NULL;
    }

    pid_t pid = forkChild();
    if (pid == -1) {
        printf("Fork failed\n");
        return NULL;
    }

    if (pid == 0) {
        redirectStdout(pipefd);
        closeFileDescriptors(pipefd[0], pipefd[1]);
        executeChildCommand(command);
    } else {
        closeFileDescriptors(pipefd[1], pipefd[0]);
        result = receivePipeData(pipefd);
        wait(NULL);
    }

    return result;
}

int createPipe(int pipefd[2]) {
    return pipe(pipefd);
}

pid_t forkChild() {
    return fork();
}

void redirectStdout(int pipefd[2]) {
    dup2(pipefd[1], STDOUT_FILENO);
}

void closeFileDescriptors(int fd1, int fd2) {
    close(fd1);
    close(fd2);
}

void executeChildCommand(const char* command) {
    execl("/bin/sh", "sh", "-c", command, NULL);
    printf("Command execution failed\n");
    exit(EXIT_FAILURE);
}

ssize_t readCommandOutput(int fd, char* buffer, size_t bufferSize) {
    return read(fd, buffer, bufferSize);
}

char* receivePipeData(int pipefd[2]) {
    char* result = NULL;
    int bufferSize = 128;
    int totalSize = 0;

    char buffer[bufferSize];
    ssize_t bytesRead;
    while ((bytesRead = readCommandOutput(pipefd[0], buffer, bufferSize - 1)) > 0) {
        char* temp = (char*)realloc(result, totalSize + bytesRead + 1);
        if (temp == NULL) {
            printf("Memory allocation failed\n");
            free(result);
            close(pipefd[0]);
            return NULL;
        }
        result = temp;

        memcpy(result + totalSize, buffer, bytesRead);
        totalSize += bytesRead;
    }

    close(pipefd[0]);
    if (bytesRead == -1) {
        printf("Error reading command output\n");
        free(result);
        return NULL;
    }

    result[totalSize] = '\0';

    return result;
}

void runPipedCommand(const char* command) {
    char* output = executeCommand(command);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
}

void runCommand(const char* command) {
    char* pipeSymbol = "|";
    char* pipeCommand = strstr(command, pipeSymbol);

    if (pipeCommand != NULL) {
        // Split the command into two parts at the pipe symbol
        *pipeCommand = '\0';
        pipeCommand += strlen(pipeSymbol);

        runPipedCommand(pipeCommand);
    } else {
        runPipedCommand(command);
    }
}
