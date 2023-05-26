#include "shell.h"
/**
 * cov_int_to_str - converts integer to string
 * @int_arg: integer
 * @int_str: string
 * Return: i
 */
int cov_int_to_str(int int_arg, char *int_str)
{
	int i = 0;

	if (int_arg == 0)
	{
		int_str[0] = '0';
		i = 1;
	}
	else
	{
		if (int_arg < 0)
		{
			int_str[0] = '-';
			int_arg = -int_arg;
			i = 1;
		}
		while (int_arg > 0)
		{
			int_str[i++] = '0' + (int_arg % 10);
			int_arg /= 10;
		}
	}
	return (i);
}
