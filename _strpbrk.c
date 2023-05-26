#include "shell.h"

/**
 * _strpbrk - find the first occurrence in s
 * of any charcters in the char array accept
 * @s: the string to check s for
 * @accept: the character to check in s
 * Return: returns a pointer to the character that it in accept
 * or returns null if it not found
 */
char *_strpbrk(char *s, char *accept)
{
		int k;

		while (*s)
		{
			for (k = 0; accept[k]; k++)
			{
			if (*s == accept[k])
			return (s);
			}
		s++;
		}

	return ('\0');
}
