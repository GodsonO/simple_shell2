#include "shell.h"

/**
 * _strdup - copied a string space and value
 * @str: the string to copy
 * Return: returns the copied string
 */
char *_strdup(char *str)
{
	size_t len;
	char *copy;
	char *result;

	if (str == NULL)
	{
		return (NULL);
	}

	len = _strlen(str);
	copy = malloc((len + 1) * sizeof(char));

	if (copy == NULL)
	{
		err_msg("Error: Failed to allocate memor\n");
	}

	_strcpy(copy, str);
	result = copy;
	return (result);
}
