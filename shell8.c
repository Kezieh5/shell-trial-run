#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* get_builtin - Function that look for a builtin (env, exit, etc).
* @string: string to be evaluated as builtin.
* Return: A function associated with the builtin name (success).
*/

int (*get_builtin(char *string))()
{
	unsigned int t = 0;

	while (list[t].name != NULL)
	{
		if ((_strcmp(string, list[t].name)) == 0)
		{
			return (list[t].func);
		}
		t++;
	}
	return (NULL);
}

/**
 * env - function that prints environment variables.
 * Return: Success is 0
 */

int env(void)
{
	int u = 0;

	for (u = 0; environ[u]; u++)
	{
		write(1, environ[u], _strlen(environ[u]));
		write(1, "\n", 1);
	}
	return (0);
}

/**
 * _own_exit - function that exit the terminal.
 * Return: 1 as a flag to return in main function.
 */

int _own_exit(void)
{
	return (1);
}
