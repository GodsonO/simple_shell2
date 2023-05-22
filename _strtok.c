#include "shell.h"

__thread char *strtok_context = NULL;
/**
 * _strtok - seperate strings into token
 * based on specified characters
 * @str: the string to seperate
 * @delimiters: the character to use
 * to separate
 * Return: returns the pointer to seprated words
 */
char *_strtok(char *str, char *delimiters)
{
	char *start;
	char *end;

	if (str != NULL)
	{
		strtok_context = str;
	}
	else if (strtok_context == NULL)
	{
		return NULL;
	}

	start = strtok_context;
	end = _strpbrk(strtok_context, delimiters);

	if (end != NULL)
	{
		*end = '\0';
		strtok_context = end + 1;
	}
	else
	{
		strtok_context = NULL;
	}
	return (start);
}
