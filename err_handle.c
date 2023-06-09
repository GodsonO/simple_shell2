#include "shell.h"
int cov_int_to_str(int int_arg, char *int_str);
/**
 * write_string - print err to stdout
 * @str_arg: the msg to write to stdout
 * @str_len: string length
 */
void write_string(const char *str_arg, size_t str_len)
{
	ssize_t nwrite;

	nwrite = write(2, str_arg, str_len);
	if (nwrite == -1)
	{
		sys_err("write failed");
	}
}
/**
 * reverse_string - reverses string
 * @str: string
 * @length: length of string
 * Return: void
 */
void reverse_string(char *str, int length)
{
	int i = 0;
	int j = length - 1;

	while (i < j)
	{
		char temp = str[i];

		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
/**
 * write_integer - write an integer
 * @int_arg: stores integer
 * Return: void
 */
void write_integer(int int_arg)
{
	ssize_t nwrite;
	char int_str[12];
	int str_length = cov_int_to_str(int_arg, int_str);

	reverse_string(int_str, str_length);

	nwrite = write(2, int_str, str_length);
	if (nwrite == -1)
	{
		sys_err("write failed");
	}
}
/**
 * write_character- write a character
 * @c: stores char
 * Return: void
 */
void write_character(char c)
{
	ssize_t nwrite;

	nwrite = write(2, &c, 1);
	if (nwrite == -1)
	{
		sys_err("write failed");
	}
}
/**
 * sys_err - system error
 * @str: string
 * Return: void
 */
void sys_err(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
/**
 * err_msg - error message
 * @format: a pointer char
 * Return: void
 */
void err_msg(const char *format, ...)
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
