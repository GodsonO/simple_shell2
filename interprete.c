#include"shell.h"

/**
 * is_builtin_command - built in command
 * @command: pointer char
 * Return: 0
 */

int is_builtin_command(const char *command)
{
	int i;
	const char *builtins[] = {"cd", "help", "exit"};
	int num_builtins = sizeof(builtins) / sizeof(char *);

	for (i = 0; i < num_builtins; ++i)
	{
		if (_strcmp(command, builtins[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}
/**
 * execute_builtin_command - execute built in command
 * @command: pointer char
 * @arguments: pointer  to a pointer char
 */
void execute_builtin_command(const char *command, char **arguments)
{
	if (_strcmp(command, "cd") == 0)
	{
		if (arguments[1] == NULL)
		{
			err_msg("cd: directory argument missing\n");
		}
		else if (arguments[2] != NULL)
		{
			err_msg("cd: invalid number of arguments\n");
		}
		else
		{
			if (chdir(arguments[1]) != 0)
			{
				err_msg("cd: Directory change failed\n");
			}
		}
	}
	else if (_strcmp(command, "help") == 0)
	{
		err_msg("Help command executed\n");
	}
	else if (_strcmp(command, "exit") == 0)
	{
		my_exit(arguments);
	}
	else if (_strcmp(command, "env") == 0)
	{
		_env();
	}
	else
	{
		err_msg("Unknown command: %s\n", command);
	}
}
/**
 * execute_external_command - executes external command
 * @command: pointer char
 * @arguments: pointer to pointer char
 */
void execute_external_command(const char *command, char **arguments)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (_execvp(command, arguments) == -1)
		{
			err_msg("Error executing the command '%s'\n", command);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		err_msg("Error forking process\n");
	}
	else
	{
		wait(NULL);
	}
}
/**
 * free_arguments - frees arguments
 * @arguments: pointer to a pointer char
 */
void free_arguments(char **arguments)
{
	int i;

	for (i = 0; arguments[i] != NULL; ++i)
	{
		free(arguments[i]);
	}
}
