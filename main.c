#include "shell.h"
/**
 * main - implements a unix cmd interpreter
 * @ac: no of arrays
 * @av: array of strings read
 * Return: returns 0 if successful and -1 on failure
 */
int main(int ac, char *av[])
{
	(void) av;

	if (isatty(STDIN_FILENO) == 1)
	{
		ssize_t nwrite;
		const char *command;
		char *input = NULL;
		char **arguments = NULL;

		while (1)
		{
			nwrite = write(STDOUT_FILENO, "$ ", 2);
			if (nwrite == -1)
			{
				sys_err("write");
			}
			input = usr_input();

			if (input == NULL)
			{
				putchar('\n');
				break;
			}
			arguments = token(input);

			command = arguments[0];
			if (is_builtin_command(command))
			{
				execute_builtin_command(command, arguments);
			}
			else
			{
				execute_external_command(command, arguments);
			}

			free(input);
			free_arguments(arguments);
		}
	}
	else
	{
		if (ac > 2)
		{
			char *user_input = usr_input();
			char **tokens = token(user_input);

			if (is_builtin_command(tokens[0]))
			{
				execute_builtin_command(tokens[0], tokens);
			}
			else
			{
				execute_external_command(tokens[0], tokens);
			}
			free(user_input);
			free_arguments(tokens);
		}
		else
		{
			err_msg("usage: echo");
		}
	}
	return (0);
}
