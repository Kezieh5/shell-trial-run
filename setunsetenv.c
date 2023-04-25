#include "shell.h"

int set_env(const char *name, const char *value);
int unset_env(const char *name);

/**
 * set_env - sets a new environment variable, or modifies an existing one
 * @name: the name of the variable to set
 * @value: the value to set the variable to
 * Return: 0 on success, 1 on failure
 */
int set_env(const char *name, const char *value)
{
    if (name == NULL || value == NULL) {
        _eputs("set_env: invalid arguments\n");
        return 1;
    }

    char *env_var = malloc(strlen(name) + strlen(value) + 2);
    if (env_var == NULL) {
        _eputs("set_env: failed to allocate memory\n");
        return 1;
    }

    sprintf(env_var, "%s=%s", name, value);

    if (putenv(env_var) != 0) {
        perror("set_env");
        free(env_var);
        return 1;
    }

    free(env_var);

    return 0;
}

/**
 * unset_env - removes an environment variable
 * @name: the name of the variable to unset
 * Return: 0 on success, 1 on failure
 */
int unset_env(const char *name)
{
    if (name == NULL) {
        _eputs("unset_env: invalid argument\n");
        return 1;
    }

    if (unsetenv(name) != 0) {
        perror("unset_env");
        return 1;
    }

    return 0;
}

/**
 * setenv_builtin - implementation of the setenv built-in command
 * @info: the command info struct
 * Return: 0 on success, 1 on failure
 */
int setenv_builtin(info_t *info)
{
    if (info->argc != 3) {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (set_env(info->argv[1], info->argv[2]) != 0) {
        return 1;
    }

    return 0;
}

/**
 * unsetenv_builtin - implementation of the unsetenv built-in command
 * @info: the command info struct
 * Return: 0 on success, 1 on failure
 */
int unsetenv_builtin(info_t *info)
{
    if (info->argc != 2) {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (unset_env(info->argv[1]) != 0) {
        return 1;
    }

    return 0;
}
