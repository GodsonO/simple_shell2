#include "shell.h"

/**
 * usage_err - print err to stdout
 * @str: the msg to write to stdout
 *
 */

void print_err(const char *str, ...)
{
	va_list arg_list;
	char *arg_value;
	int arg2_value;
	char num_str[20];
	ssize_t nwrite;
	const char *ch;
	va_start(arg_list, str);


	ch = str;

	while(*ch)
	{
		if (*ch == '%' && *(ch + 1) == 's')
		{
			ch += 2;

			arg_value = va_arg(arg_list, char *);
			write_str(arg_value);
		}
		else if (*ch == '%' && *(ch + 1) == 'd')
		{
			ch += 2;
			arg2_value = va_arg(arg_list, int);
			num_str[20];
			write_int(arg2_value);
		}
		else
		{
			nwrite = write(STDERR_FILENO, ch, 1);
			if (nwrite == -1)
			{
				sys_err("write");
			}
			ch++;
		}
	}
	va_end(arg_list);
}
