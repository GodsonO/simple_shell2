#include "shell.h"

/**
 * _strcspn - 
 * @str: input string
 * @charset: the charcters to search for
 * Return: returns the length of string
 * until chacterset
 */

size_t _strcspn(const char *str, const char *charset)
{
	size_t length = 0;

	while(*str)
	{
		const char *c = charset;
		while (*c)
		{
			if (*str == *c)
			{
				return (length);
			}
			c++;
		}
		str++;
		length++;
	}
	return (length);
}
