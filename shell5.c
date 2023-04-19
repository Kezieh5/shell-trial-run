#include "shell.h"

/**
 * print_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: Always 0
 */
int print_env(info_t *info)
{
    print_list_str(get_environ(info));
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
    size_t q;

    for (q = 0; env[q]; q++)
    {
        if (_starts_with(env[q], name))
            return env[q] + _strlen(name) + 1;
    }

    return NULL;
}

/**
 * set_env_var - initializes a new environment variable or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 * Return: 0 on success, 1 on failure
 */
int set_env_var(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

/**
 * unset_env_var - removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0 on success, 1 on failure
 */
int unset_env_var(info_t *info)
{
    int q;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (q = 1; q <= info->argc; q++)
        _unsetenv(info, info->argv[q]);

    return 0;
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
    size_t q;

    for (q = 0; environ[q]; q++)
        add_node_end(&node, environ[q], 0);

    info->env = node;
    info->environ = NULL;
    info->env_changed = 0;

    return 0;
}
