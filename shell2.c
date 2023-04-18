#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt(const char* prompt) {
    printf("%s", prompt);
    fflush(stdout);
}
int main(int argc, char *argv[]) {
    while (1) {
        display_prompt("$ ");
        
        // Read the user's command from stdin
        char command[MAX_COMMAND_LENGTH];
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // End of file condition (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Parse the command and its arguments
        #define MAX_ARGS ((MAX_COMMAND_LENGTH / 2) + 1)
        char* argv[MAX_ARGS];
	int argc = 0;
        for (char *token = strtok(command, " "); token != NULL; token = strtok(NULL, " ")) 
	{
         argv[argc++] = token;
	}
        argv[argc] = NULL;


        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execvp(argv[0], argv);
            // If execvp returns, the command could not be executed
            perror(argv[0]);
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

