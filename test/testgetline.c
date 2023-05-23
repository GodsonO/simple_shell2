#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static int buffer_index = 0;
static int buffer_size = 0;

static ssize_t read_buffer(FILE* stream)
{
    buffer_size = read(fileno(stream), buffer, BUFFER_SIZE);
    buffer_index = 0;

    if (buffer_size <= 0)
    {
        return (-1);
    }

    return buffer_size;
}

static int find_newline_index()
{
    for (int i = buffer_index; i < buffer_size; i++)
    {
        if (buffer[i] == '\n')
        {
            return i;
        }
    }

    return -1;
}

static ssize_t process_line(char** lineptr, size_t* n, int newline_index)
{
    size_t line_length = newline_index - buffer_index + 1;
    if (line_length > *n)
    {
        *lineptr = realloc(*lineptr, line_length);
        *n = line_length;
        if (*lineptr == NULL)
        {
            return (-1);
        }
    }

    memcpy(*lineptr, &buffer[buffer_index], line_length);
    (*lineptr)[line_length - 1] = '\0';

    buffer_index = newline_index + 1;
    return line_length;
}

static ssize_t process_buffer(char** lineptr, size_t* n)
{
    size_t buffer_length = buffer_size - buffer_index;
    size_t current_length = *n;

    *lineptr = realloc(*lineptr, current_length + buffer_length + 1);

    if (*lineptr == NULL)
    {
        return (-1);
    }

    memcpy(*lineptr + current_length, &buffer[buffer_index], buffer_length);
    *n += buffer_length;
    (*lineptr)[*n] = '\0';

    buffer_index = buffer_size;
    return buffer_length;
}

ssize_t _getline(char** lineptr, size_t* n, FILE* stream)
{
    if (buffer_index >= buffer_size)
    {
        if (read_buffer(stream) <= 0)
        {
            return -1;
        }
    }

    int newline_index = find_newline_index();
    if (newline_index >= 0)
    {
        return process_line(lineptr, n, newline_index);
    }
    else
    {
        return process_buffer(lineptr, n);
    }
}

int main()
{
    char* line = NULL;
    size_t line_length = 0;
    ssize_t bytes_read;

    printf("Enter lines of text (Ctrl+D to exit):\n");

    while ((bytes_read = getline(&line, &line_length, stdin)) != -1)
    {
        printf("Line read: %s\n", line);
    }

    free(line);

    return 0;
}

