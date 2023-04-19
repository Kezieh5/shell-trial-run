#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: A pointer to the string array containing the environment variables
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, const char *var)
{
	list_t **head = &(info->env);
	list_t *node = *head;
	size_t i = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		if (_starts_with(node->str, var))
		{
			info->env_changed = delete_node_at_index(head, i);
			node = *head;
			continue;
		}
		node = node->next;
		i++;
	}

	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *           or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(info_t *info, const char *var, const char *value)
{
	char *buf = NULL;
	list_t **head = &(info->env);
	list_t *node;
	size_t var_len, value_len;

	if (!var || !value)
		return (0);

	var_len = _strlen(var);
	value_len = _strlen(value);

	buf = malloc(sizeof(char) * (var_len + value_len + 2));
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = *head;
	while (node)
	{
		if (_starts_with(node->str, var))
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(head, buf, 0);
	free(buf);
	info->env_changed = 1;

	return (0);
}
