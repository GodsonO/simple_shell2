#include "shell.h"

/**
 * _strchr - searches for a string
 * @str: the input string ot comapare
 * @c: the target character
 */

char *_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
