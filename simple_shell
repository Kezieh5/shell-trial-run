#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 126

void display_prompt(const char* prompt) {
    write(STDOUT_FILENO, prompt, strlen(prompt));
    fsync(STDOUT_FILENO);
}

int main() {
    while (1) {
        display_prompt("$ ");

	       //	Read the user's command from stdin
        char command[MAX_COMMAND_LENGTH];
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // End of file condition (Ctrl+D)
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
	command[strcspn(command, "\n")] = '\0';
        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(command, command, NULL);
            // If execlp returns, the command could not be executed
            perror(command);
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                const char* error_message = "Command '";
    write(STDERR_FILENO, error_message, strlen(error_message));
    write(STDERR_FILENO, command, strlen(command));
    const char* error_message_end = "' could not be executed.\n";
                write(STDERR_FILENO, error_message_end, strlen(error_message_end));
            }
        }
    }

    return 0;
}
