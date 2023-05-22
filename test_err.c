
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


void write_string(const char* str_arg, size_t str_len)
{
    write(2, str_arg, str_len);
}
int convert_integer_to_string(int int_arg, char* int_str)
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

    return i;
}
void reverse_string(char* str, int length)
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
void write_integer(int int_arg)
{
    char int_str[12];  // assuming a maximum of 11 digits for an integer
    int str_length = convert_integer_to_string(int_arg, int_str);

    reverse_string(int_str, str_length);

    write(2, int_str, str_length);
}
void write_character(char c)
{
    write(2, &c, 1);
}
void err_msg(const char* format, ...)

    va_list argp;
    va_start(argp, format);

    const char* p = format;

    while (*p != '\0')
    {
        if (*p == '%' && *(p + 1) != '\0')
        {
            switch (*(p + 1))
            {
                case 's':
                {
                    char* str_arg = va_arg(argp, char*);
                    size_t str_len = strlen(str_arg);
                    write_string(str_arg, str_len);
                    p += 2;
                    break;
                }
                case 'd':
                {
                    int int_arg = va_arg(argp, int);
                    write_integer(int_arg);
                    p += 2;
                    break;
                }
                default:
                {
                    write_character(*p);
                    p += 1;
                    break;
                }
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

int main()
{
    err_msg("This is a test message with an integer: %d and a string: %s\n", 42, "Hello, world!");

    return 0;
}
