#include "shell.h"

/**
 * usr_input - prints prompt and gets cmd line char
 * Return: returns the read cmd line char
 */
char *usr_input(void)
{
	ssize_t ngetline;
	char *lineptr = NULL;
	char *result = lineptr;
	size_t n = 0;

	ngetline = _getline(&lineptr, &n, stdin);
	if (ngetline != -1)
	{
		result = lineptr;
		lineptr = NULL;
		return(result);
	}
	else
	{
		free(lineptr);
		return(NULL);
	}
}
