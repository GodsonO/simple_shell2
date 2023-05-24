#include "shell.h"
/**
 * print_err - print err to stdout
 * @str: the msg to write to stdout
 *
 */
void print_err(const char *format, ...)
{
	va_list argp;
	char *str_arg;
	size_t str_len;
	int int_arg;

	const char *p = format;

	va_start(argp, format);

	while (*p != '\0')
	{
		if (*p == '%' && *(p + 1) != '\0')
		{
			if (*(p + 1) == 's')
			{
				str_arg = va_arg(argp, char *);
				str_len = strlen(str_arg);
				write_string(str_arg, str_len);
				p += 2;
				break;
			}
			else if (*(p + 1) == 'd')
			{
				int_arg = va_arg(argp, int);
				write_integer(int_arg);
				p += 2;
				break;
			}
			else
			{
				write_character(*p);
				p += 1;
				break;
			}
		}
		else
		{
			write_character(*p);
			p += 1;
		}
	}
	va_end(argp);
}
