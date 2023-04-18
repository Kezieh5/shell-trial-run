#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 126

void display_prompt(const char* prompt) {
    printf("%s", prompt);
    fflush(stdout);
}

int main() {
    while (1) {
        display_prompt("$ ");

	       //	Read the user's command from stdin
        char command[MAX_COMMAND_LENGTH];
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // End of file condition (Ctrl+D)
            printf("\n");
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
                printf("Command '%s' could not be executed.\n", command);
            }
        }
    }

    return 0;
}

