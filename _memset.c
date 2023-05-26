#include "shell.h"

/**
 * _memset - initializes the memory s is pointing to
 * with char in b
 * @s: the pointer to the memory block to be initialized
 * @b: the charater to use to initialize s
 * @n: the num of byte to fill
 * Return: it return the address of the array s is
 * pointing to
 *
 *
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;
	char *ptr = s;

	for (i = 0; i < n; i++)
	{
		*ptr++ = b;
	}
	return (s);
}
