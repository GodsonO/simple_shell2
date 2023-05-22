#include "shell.h"

/**
 * main - implements a unix cmd interpreter
 * @ac: no of arrays
 * @av: array of strings read
 * Return: returns 0 if successful and -1 on failure
 */

int main(int ac, char *av[])
{
	(void) ac;
	(void) av;

	if (isatty(STDIN_FILENO) == 1)
	{
		ssize_t nwrite;
		char *input = NULL;
		char **tokenized_input = NULL;
		while(1)
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
			grammer(tokenized_input, ac, av);

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
			//printf("this is non-interactive mode");

		}
	}
	return(0);
}
