#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

int main(int argc, char **argv) {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_INPUT_LENGTH / 2 + 1];

    while (1) {
        printf("$ ");
        fflush(stdout);

        // read input from stdin
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // ignore comments (anything after # character)
        char *comment_start = strchr(input, '#');
        if (comment_start != NULL) {
            *comment_start = '\0';
        }

        // remove trailing newline character
        char *newline = strchr(input, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        // tokenize input string
        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        // handle empty input
        if (argc == 0) {
            continue;
        }

        // handle exit command
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // fork a child process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // child process
            if (execvp(args[0], args) == -1) {
                perror("execvp failed");
                exit(1);
            }
        } else {
            // parent process
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
