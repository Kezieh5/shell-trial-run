#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define BUFFER_SIZE 1024

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    while (1) {
        // Print prompt
        write(STDOUT_FILENO, "$ ", 2);

        // Read input from user
        ssize_t num_chars = getline(&buffer, &bufsize, stdin);
        if (num_chars == -1) {
            // End of file or error, exit
            break;
        }

        // Remove newline character
        if (buffer[num_chars - 1] == '\n') {
            buffer[num_chars - 1] = '\0';
        }

        // Execute command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *args[2] = {buffer, NULL};
            execvp(args[0], args);

            // If we get here, execvp failed
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }

    // Free buffer memory
    free(buffer);

    return 0;
}
