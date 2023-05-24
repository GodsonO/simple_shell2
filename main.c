#include "shell.h"

/**
 * main - implements a unix cmd interpreter
 * @ac: no of arrays
 * @av: array of strings read
 * Return: returns 0 if successful and -1 on failure
 */

int main(int ac, char *av[])
{
	if (isatty(STDIN_FILENO) == 1)
	{
		int stats;
		ssize_t nwrite;
		char *input = NULL;
		char **tokenized_input = NULL;

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
			tokenized_input = token(input);
			stats = grammer(tokenized_input, ac, av);
			if (stats == 0)
			{
				execute(tokenized_input, ac, av);
			}
			free(input);
			free_token(tokenized_input);
		}
	}
	else
	{
		if (ac > 2)
		{
			char *user_input = usr_input();
			char **tokens = token(user_input);

			if (grammer(tokens, ac, av) == 0)
			{
				exec_cmnd(tokens);
			}
		}
		else
		{
			err_msg("usage: echo");
		}
	}
	return (0);
}
