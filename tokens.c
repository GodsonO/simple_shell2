#include "shell.h"

/**
 * token - it seprates the string into tokens
 * @str: the string to seperate
 * Return: returns the tokens
 */

char **token(char *str)
{
	size_t tlen;
	size_t j = 0;
	char delim[] = " \t\n";
	char *str_copy = _strdup(str);
	char *toks = _strtok(str, delim);
	char **token = malloc(sizeof(char *) * (MAX_LEN));

	(void) str_copy;

	if (token == NULL)
		err_msg("Malloc failed");


	while(toks != NULL && j <= MAX_LEN)
	{
		while(*toks == ' ' || *toks == '\t')
			toks++;

		tlen = strlen(toks);

		while(tlen > 0 && (toks[tlen - 1] == ' ' || toks[tlen - 1] == '\t'))
			tlen--;

		if (tlen > 0)
		{
			token[j] = _strdup(toks);
			j++;
		}
		toks = _strtok(NULL, delim);
	}

	return(token);
}
