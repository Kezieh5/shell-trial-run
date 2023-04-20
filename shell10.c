#include "shell.h"

void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_pwd(void);

/**
 * help_pwd - Displays information on the shellby builtin command 'pwd'.
 */
void help_pwd(void)
{
    char *msg = "pwd: pwd\n\tPrints the current working directory.\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_alias - Displays information on the shellby builtin command 'alias'.
 */
void help_alias(void)
{
	 char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "\n\talias: Prints a list of all aliases, one per line, in ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = " the aliases name, name2, etc. one per line, in the ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = " an alias for each NAME whose VALUE is given. If NAME ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "is already an alias, replace its value with VALUE.\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_cd - Displays information on the shellby builtin command 'cd'.
 */
void help_cd(void)
{
    char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "command is interpreted as cd $HOME. If the argument '-' is";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "\tThe environment variables PWD and OLDPWD are updated ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "after a change of directory.\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_exit - Displays information on the shellby builtin command 'exit'.
 */
void help_exit(void)
{
    char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

        write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "If a STATUS is specified, it will be used as the exit status.";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = " Otherwise, the exit status will be 0.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_help - Displays information on the shellby builtin command 'help'.
 */
void help_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

  
