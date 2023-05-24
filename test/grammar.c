#include "shell.h"

/**
 * grammer - define the grammer rules
 * @token: the tokenized word
 *
 */
int grammer(char **token, int ac, char *av[])
{

	int m, k, i, j, len = 0;
	command check;

	check.command = token[0];

	(void) ac;
	printf("this is check.command -> %s\n", check.command);

	for (j = 0; token[j] != NULL; j++)
	{
		len++;
	}

	for (i = 1; i < len; i++)
	{

		if (token[i][0] == '-')
		{
			cmd_insert_opt(&check, token[i]);
		}
		else
		{
			cmd_insert_arg(&check, token[i]);
		}
	}

	if (err_cmd(&check) == 1)
	{
		err_msg("%s: %s: not found\n", av[0], check.command);
	}
	else if (err_opt(&check) == 1)
	{
		err_msg("%s: invalid option --   %s\nTry '%s --help' for more information\n", check.command, check.options[0], check.command);
	}


	for (k = 0; k < check.num_opt; k++)
	{
		printf("options: %s\n", check.options[k]);
	}
	for (m = 0; m < check.num_arg; m++)
	{
		printf("arguments: %s\n", check.arguments[m]);
	}
	return (0);
}
void cmd_insert_opt(command *cmd, char *opt)
{
	if (cmd->avl_opt == 0)
	{
		cmd->avl_opt = 1;
		cmd->options = malloc(sizeof(char *));
	}
	else if (cmd->num_opt >= cmd->avl_opt)
	{
		cmd->avl_opt *= 2;
		cmd->options = realloc(cmd->options, sizeof(char *) * cmd->avl_opt);
	}
	cmd->options[cmd->num_opt] = opt;
	cmd->num_opt++;
	cmd->options[cmd->num_opt] = NULL;
}
void cmd_insert_arg(command *cmd, char *arg)
{
	if (cmd->avl_arg == 0)
	{
		cmd->avl_arg = 1;
		cmd->arguments = malloc(sizeof(char *));
	}
	else if (cmd->num_arg >= cmd->avl_arg)
	{
		cmd->avl_arg *= 2;
		cmd->arguments = realloc(cmd->arguments, sizeof(char *) * cmd->avl_arg);
	}
	cmd->arguments[cmd->num_arg] = arg;
	cmd->num_arg++;
	cmd->arguments[cmd->num_arg] = NULL;
}
int err_cmd(command *cmd, char **token, int ac, char *av[])
{
	int i;
	char *valid_commands[] = {"exit", "cd", "mkdir"};
	int num_valid_cmd = sizeof(valid_commands) / sizeof(valid_commands[0]);
	int is_valid_command = 0;


	for (i = 0; i < num_valid_cmd; i++)
	{
		if (_strcmp(cmd->command, valid_commands[i]) == 0)
		{
			is_valid_command++;
			break;
		}
	}
	if (is_valid_command > 0 && err_opt(cmd) == 0)
	{
		printf("%s is a builtin\n", cmd->command);
		execute(token, ac, av);

		return (0);
	}
	else if ((access(cmd->command, F_OK | X_OK) != -1) && err_opt(cmd) == 0)
	{
		exec_cmnd(token);
		printf("%s is a executable\n", cmd->command);
		return (0);
	}
	else
	{
		err_msg("Unknown: command");
		return (0);
	}
	return (1);
}

int err_opt(command *cmd)
{
	int i, j, k, m, is_valid;
	char *valid_options[] = {"-l", "-a"};
	int num_valid_options = sizeof(valid_options) / sizeof(valid_options[0]);
	int is_invalid_option_found = 0;

	for (j = 0; j < cmd->num_opt; j++)
	{
		if (cmd->options[j][0] == '-' && cmd->options[j][1] != '\0')
		{
			is_valid = 0;
			for (i = 1; cmd->options[j][i] != '\0'; i++)
			{
				for (m = 0; m < num_valid_options; m++)
				{
					if (cmd->options[j][i] == valid_options[m][1])
					{
						is_valid++;
					}
				}
				if (!is_valid)
				{
					is_invalid_option_found++;
					break;
				}
			}
		}
		else
		{
			for (k = 0; k < num_valid_options; k++)
			{
				if (_strcmp(cmd->options[j], valid_options[k]) == 0)
				{
					is_valid = 1;
					break;
				}
			}
			if (!is_valid)
			{
				is_invalid_option_found = 1;
				break;
			}
		}
	}
	if (is_invalid_option_found)
	{
		return (1);
	}
	return (0);
}
int is_path(char *path)
{
	if (path == NULL || _strlen(path) == 0)
		return (1);

	if (path[0] == '/')
		return (0);

	return (1);
}

/*int err_arg(command *cmd)
{
	int k, j, i;
	int wildcard = 0;
	char **exp_results = NULL;

	for (k = 0; k < cmd->num_arg; k++)
	{
		if (_strpbrk(arguments[k], "*?[]{}") != NULL)
		{
			wildcard = 1;
			break;
		}
	}
	if (wildcard)
	{
		for (j = 0; j < cmd->num_arg; j++)
		{
			exp_results = expand(cmd->arguments[j]);

			if (exp_restults != NULl)
			{
				for (i = 0; exp_results[i] != NULL; i++)
				{
					printf("Expanded result %d: %s\n", i + 1, exp_results[i]);
					free(exp_results[i]);
				}
				free(exp_results);
			}

		}
	}
}*/

int match(const char *pattern, const char *text)
{
	if (*pattern == '\0' && *text == '\0')
	{
		return (1);
	}
	if (*pattern == '*' && *(pattern + 1) != '\0' && *text == '\0')
	{
		return (0);
	}
	if (*pattern == '?' || *pattern == *text)
	{
		return (match(pattern + 1, text + 1));
	}
	if (*pattern == '*')
	{
		return (match(pattern + 1, text) || match(pattern, text + 1));
	}
	return (0);
}
/*
char **expand(char *pattern)
{
	DIR *dir;
	struct dirent *entry;
	size_t prefixlen;
	char *prefix = NULL;
	char *suffix = NULL;
	char **results = NULL;
	char **temp = NULL;
	int result_count = 0;

	char *asterisk = _strchr(pattern, '*');
	if (asterisk != NULL)
	{
		prefixlen = asterisk - pattern;
		prefix = malloc((prefixlen + 1) * sizeof(char));
		if (prefix == NULL)
		{
			err_msg("malloc failed");
		}
		_strncpy(prefix, pattern, prefixlen);
		prefix[prefixlen] = '\0';

		suffix = _strdup(asterisk + 1);
	}
	else
	{
		prefix = strdup(pattern);
		suffix = malloc(sizeof(char));
		*suffix = '\0';
	}

	dir = opendir(".");
	if (dir == NULL)
	{
		sys_err("opendir");
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (match(prefix, entry->d_name) && match(suffix, entry->d_name + _strlen(prefix)))
		{
			result_count++;
			temp = realloc(results, (result_count + 1) * sizeof(char *));
			if (temp == NULL)
			{
				err_msg("realloc failed");
				break;
			}
			results = temp;

			results[result_count -1] = _strdup(entry->d_name);
			results[result_count] = NULL;
		}
	}

	closedir(dir);
	free(prefix);
	free(suffix);

	return (results);
}
*/
