#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 256
#define STDOUT 1

void get_full_path(const char* command, char* path_buf) {
    char* path = getenv("PATH");
    size_t path_len = strlen(path);

    for (size_t k = 0, u = 0; k <= path_len; k++) {
        if (path[k] == ':' || k == path_len) {
            snprintf(path_buf, MAX_COMMAND_LENGTH, "%.*s/%s", (int)(k-u), &path[u], command);
            if (access(path_buf, X_OK) == 0) {
                // The command exists and is executable
                return;
            }
            u = k + 1;
        }
    }

    // The command does not exist
     char err_msg[MAX_COMMAND_LENGTH];
    size_t err_msg_len = snprintf(err_msg, MAX_COMMAND_LENGTH, "Command '%s' not found.\n", command);
    write(STDERR_FILENO, err_msg, err_msg_len);
    exit(EXIT_FAILURE);
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char path_buf[MAX_COMMAND_LENGTH];

    while (1) {
        char prompt[] = ">> ";
        write(STDOUT, prompt, sizeof(prompt) - 1);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // Handle end of file
            char newline[] = "\n";
            write(STDOUT, newline, sizeof(newline) - 1);
            exit(EXIT_SUCCESS);
        }

        // Remove the newline character from the command
        size_t command_len = strlen(command);
        if (command[command_len-1] == '\n') {
            command[command_len-1] = '\0';
        }

        // Get the full path of the command
        get_full_path(command, path_buf);

        // Execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execv(path_buf, (char* const[]) { path_buf, NULL });
            // If we reach this point, execv has failed
            char error_msg[MAX_COMMAND_LENGTH];
            int n = snprintf(error_msg, MAX_COMMAND_LENGTH, "Error: command '%s' not found or not executable.\n", command);
            write(STDOUT, error_msg, n);
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            // Error forking
            char error_msg[MAX_COMMAND_LENGTH];
            int n = snprintf(error_msg, MAX_COMMAND_LENGTH, "Error: could not fork.\n");
            write(STDOUT, error_msg, n);
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
