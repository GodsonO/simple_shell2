#include "shell.h"
/**
 * _putchar - write to the file discriptor for the stdout
 * @c: receives the argument character
 */


void _putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}
