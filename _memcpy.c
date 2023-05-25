#include "shell.h"

/**
 * _memcpy - copies a character form one
 * array to another array
 * @dest: the destination of the copied char
 * @src: the array to copy from
 * @n: the amount of the first byte to copy from
 * Return: returns the address of the pointer to
 * the destination i.e dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;
	char *s = src;
	char *d = dest;

	for (i = 0; i < n; i++)
	{
		*d++ = *s++;
	}
	return (dest);
}
