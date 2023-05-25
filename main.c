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
		char *command;
		char *pipe_token;
		char *command1;
		char *command2;

		if (ac < 2)
		{
			err_msg("Usage: %s command\n", av[0]);
		}
		command = usr_input();
		pipe_token = _strstr(command, "|");
		if(pipe_token != NULL)
		{
			*pipe_token = '\0';
			command1 = command;
			command2 = pipe_token + 1;

			while(*command1 == ' ') command1++;
			while (*(command2++) == ' ');
			*(--command2) = '\0';

			execute_piped_commands(command1, command2);
		}
		else
		{
			non_int_execute_command(command);
		}
	}
	return (0);
}
