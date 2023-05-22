#include "shell.h"

/**
 * _strcat - appends two strings together
 * @dest: the string to copy to
 * @src: the source string to be copied
 * Return: returns the pointer
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*ptr)
	{
		ptr++;
	}
	while (*src)
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}
