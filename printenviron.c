#include "shell.h"

/**
 * print_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int _myenv(info_t *info)
{
    char **env = info->env;
    for (int i = 0; env[i] != NULL; i++) {
        puts(env[i]);
    }
    return 0;
}
/**
 * get_env_var - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * @name: env var name
 * Return: the value of the variable, or NULL if not found
 */
char *get_env_var(info_t *info, const char *name)
{
    char **env = get_environ(info);
    size_t i = 0;

    while (env[i] != NULL) {
        if (_starts_with(env[i], name)) {
            return env[i] + _strlen(name) + 1;
        }
        i++;
    }

    return NULL;
}
/**
 * unset_env_var - removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0 on success, 1 on failure
 */
int set_env_var(info_t *info)
{
    switch (info->argc) {
        case 1:
            _eputs("Missing argument(s)\n");
            return 1;
        case 2:
            _eputs("Missing value\n");
            return 1;
        case 3:
            return _setenv(info, info->argv[1], info->argv[2]) ? 1 : 0;
        default:
            _eputs("Too many arguments\n");
            return 1;
    }
}
/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    char **envp = environ;

    for (; *envp; envp++)
        add_node_end(&node, *envp, 0);

    info->env = node;
    info->environ = NULL;
    info->env_changed = 0;

    return 0;
}
