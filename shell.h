#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define MAX_LEN 100
#define MAX_CMDS 10
#define BUFFER_SIZE 1024

extern char **environ;


/**
 * struct grammar_rule - grammer rule
 * @command: a string
 * @num_opt: integer
 * @avl_opt: integer
 * @options: pointer to a pointer char
 * @num_arg: integer
 * @avl_arg: integer
 * @arguments: string
 */
typedef struct grammar_rule
{
	char *command;
	int num_opt;
	int avl_opt;
	char **options;
	int num_arg;
	int avl_arg;
	char **arguments;
} command;
/**
 * struct simplecommand - simple command
 * @num_of_arg: number of arguments
 * @num_of_avail_arg: number of available arguments
 * @arg: the string
 */
typedef struct simplecommand
{
	int num_of_arg;
	int num_of_avail_arg;
	char **arg;
} cmd;

int non_int_execute_command(char *command);
void execute_piped_commands(char *command1, char *command2);
void free_arguments(char **arguments);
void execute_external_command(const char *command, char **arguments);
void execute_builtin_command(const char *command, char **arguments);
int is_builtin_command(const char *command);
void write_str(const char *str_arg, size_t str_len);
int cov_int_to_str(int int_arg, char *int_str);
void rev_str(char *str, int length);
void write_int(int int_arg);
void write_char(char c);
void print(const char *format, ...);
int _fileno(FILE *stream);
void exec_cmnd(char **command);
void _env(void);
void _printenv(void);
int _atoi(char *s);
void my_exit(char **arg);
char *_strchr(const char *str, int c);
size_t _strcspn(const char *str, const char *charset);
int _dup2(int oldfd, int newfd);
int _execvp(const char *cmd, char *const arguments[]);
int _fcntl(int fd, int cmd, ...);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strcat(char *dest, char *src);
char *_getenv(const char *name);
char *_strtok(char *str, char *delimiters);
char *_strstr(char *haystack, char *needle);
char *_strpbrk(char *s, char *accept);
char *_memcpy(char *dest, char *src, unsigned int n);
char *_memset(char *s, char b, unsigned int n);
char *_strncat(char *dest, const char *src, int n);
char *_strncpy(char *dest, char *src, int n);
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);
int _strlen(const char *s);
void _putchar(char c);
void _puts(char *str);
int _strcmp(const char *s1, const char *s2);
void puts2(char *str);
int _strncmp(char *s1, const char *s2, size_t n);
void print_err(const char *str, ...);

void write_string(const char *str_arg, size_t str_len);
int convert_integer_to_string(int int_arg, char *int_str);
void write_integer(int int_arg);
void write_character(char c);
void reverse_string(char *str, int length);
char *find_path(char *filename);
int is_path(char *path);
int grammer(char **token, int ac, char *av[]);
void cmd_insert_opt(command *cmd, char *opt);
void cmd_insert_arg(command *cmd, char *arg);
int err_cmd(command *cmd, char **token, int ac, char *av[]);
int err_opt(command *cmd);
int err_arg(command *cmd);
int match(const char *pattern, const char *text);
char *exp_result(char *pattern);
void execute(char **token, int ac, char *av[]);
void insert_arg(char **str);
void free_token(char **token);
void sys_err(const char *str);
void err_msg(const char *format, ...);
char *usr_input();
char **token(char *str);
int exe_command(char *c);
#endif /*SHELL_H*/
