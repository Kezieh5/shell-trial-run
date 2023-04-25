#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parater struct
 * @buf: the char buffer
 * @x: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *x)
{
    size_t b = *x;
    int found = 0;

    if (buf[b] == '|' && buf[b + 1] == '|') {
        buf[b] = 0;
        b++;
        info->cmd_buf_type = CMD_OR;
        found = 1;
    } else if (buf[b] == '&' && buf[b + 1] == '&') {
        buf[b] = 0;
        b++;
        info->cmd_buf_type = CMD_AND;
        found = 1;
    } else if (buf[b] == ';') {
        buf[b] = 0;
        info->cmd_buf_type = CMD_CHAIN;
        found = 1;
    }

    *x = b;
    return found;
}
/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @x: address of current position in buf
 * @u: starting position in buf
 * @len: length of buf
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *x, size_t u, size_t len)
{
    size_t b = *x;

    switch(info->cmd_buf_type)
    {
        case CMD_AND:
            if (info->status)
            {
                buf[u] = 0;
                b = len;
            }
            break;
        case CMD_OR:
            if (!info->status)
            {
                buf[u] = 0;
                b = len;
            }
            break;
        default:
            break;
    }

    *x = b;
}
/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
    list_t *node;
    char *alias_value, *equal_sign_pos;

    node = node_starts_with(info->alias, info->argv[0], '=');
    if (!node)
        return 0;

    alias_value = node->str;
    equal_sign_pos = strchr(alias_value, '=');
    if (!equal_sign_pos)
        return 0;

    info->argv[0] = strdup(equal_sign_pos + 1);
    if (!info->argv[0])
        return 0;

    return 1;
}
/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
    int u = 0;
    list_t *node;

    while (info->argv[u])
    {
        if (info->argv[u][0] == '$' && info->argv[u][1])
        {
            if (_strcmp(info->argv[u], "$?") == 0)
            {
                replace_string(&info->argv[u], _strdup(convert_number(info->status, 10, 0)));
            }
            else if (_strcmp(info->argv[u], "$$") == 0)
            {
                replace_string(&info->argv[u], _strdup(convert_number(getpid(), 10, 0)));
            }
            else
            {
                node = node_starts_with(info->env, &info->argv[u][1], '=');
                if (node)
                {
                    replace_string(&info->argv[u], _strdup(_strchr(node->str, '=') + 1));
                }
                else
                {
                    replace_string(&info->argv[u], _strdup(""));
                }
            }
        }
        u++;
    }
    return 0;
}
/**
 * replace_string - replaces string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new) {
    if (*old) free(*old);
    *old = new;
    return 1;
}
