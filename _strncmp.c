#include "shell.h"

/**
 * _strncmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 * @n: the max number of char to comapare
 *
 * Return: int value
 */

int _strncmp(char *s1, const char *s2, size_t n)
{
	size_t c = 0;

	while(c < n && s1[c] && s2[c] && s1[c] == s2[c])
	{
		c++;
	}

	if (c == n)
		return 0;

	return (s1[c] - s2[c]);
}
