#include "shell.h"

/**
 * _puts - prints out a string to the stdout
 * @str: receives the string
 *
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str++);
	}
	_putchar('\n');
}
