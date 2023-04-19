#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 126
#define MAX_ERROR_MSG_LENGTH 512

void display_prompt(const char* prompt) {
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

void write_error(const char* error_msg) {
    write(STDERR_FILENO, error_msg, strlen(error_msg));
}

int command_exists(const char* command) {
    char* path = getenv("PATH");
    char* dir = strtok(path, ":");

    while (dir != NULL) {
        char path_buf[MAX_COMMAND_LENGTH];
        snprintf(path_buf, MAX_COMMAND_LENGTH, "%s/%s", dir, command);
        if (access(path_buf, X_OK) == 0) {
            // The command exists and is executable
            return 1;
        }
        dir = strtok(NULL, ":");
    }

    // The command does not exist
    return 0;
}

void get_full_path(const char* command, char* path_buf) {
    char* path = getenv("PATH");
    char* dir = strtok(path, ":");

    while (dir != NULL) {
        snprintf(path_buf, MAX_COMMAND_LENGTH, "%s/%s", dir, command);
        if (access(path_buf, X_OK) == 0) {
            // The command exists and is executable
            return;
        }
        dir = strtok(NULL, ":");
    }

    // The command does not exist
    char error_msg[MAX_ERROR_MSG_LENGTH];
    snprintf(error_msg, MAX_ERROR_MSG_LENGTH, "Command '%s' not found.\n", command);
    write_error(error_msg);
    exit(EXIT_FAILURE);
}

int main() {
    while (1) {
        display_prompt("$ ");

        // Read the user's command from stdin
        char command[MAX_COMMAND_LENGTH];
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // End of file condition (Ctrl+D)
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        command[strcspn(command, "\n")] = '\0';

        // Check if the command exists
        if (command_exists(command) == 0) {
            continue;
        }

        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char path_buf[MAX_COMMAND_LENGTH];
            get_full_path(command, path_buf);
            execlp(path_buf, path_buf, NULL);
            // If execlp returns, the command could not be executed
            char error_msg[MAX_ERROR_MSG_LENGTH];
            snprintf(error_msg, MAX_ERROR_MSG_LENGTH, "Command '%s' could not be executed.\n", command);
            write_error(error_msg);
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                char error_msg[MAX_ERROR_MSG_LENGTH];
                snprintf(error_msg, MAX_ERROR_MSG_LENGTH, "Command '%s' could not be executed.\n", command);
                write_error(error_msg);
            }
        }
    }

    return 0;
}
