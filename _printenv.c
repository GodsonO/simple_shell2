#include "shell.h"
/**
 * _printenv - prints env
 */
void _printenv(void)
{
	ssize_t nwrite;

	char **ep = environ;

	while (*ep != NULL)
	{
		nwrite = write(STDOUT_FILENO, *ep, _strlen(*ep) + 1);
		putchar('\n');
		if (nwrite == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		ep++;
	}
}
