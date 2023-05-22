#include "shell.h"

/**
  * _strcpy - Copy a string
  * @dest: The paramter that stores the cpy value
  * @src: the parameter to copy from
  *
  * Return: the pointer to dest
  */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i++] = '\0';

	return (dest);
}
