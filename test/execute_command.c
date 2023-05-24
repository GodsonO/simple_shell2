#include "shell.h"

#define MAX_LINE_LENGTH 1024

/**
 *
 *
 */
int execute_cmd(char *command, int input_fd)
{
	char *args[MAX_LEN];
	char *token;
	pid_t pid;
	int arg_count = 0;
	int input_redirect = 0;
	int output_redirect = 0;
	int append_redirect = 0;
	char *input_file;
	char *output_file;
	int output_file_mode;

	token = _strtok(command, " \t\n");

	while (token != NULL && arg_count < MAX_LEN - 1)
	{
		if (_strcmp(token, "<") == 0)
		{
			input_redirect = 1;
			input_file = _strtok(NULL, " \t\n");
		}
		else if (_strcmp(token, ">") == 0)
		{
			output_redirect = 1;
			output_file = _strtok(NULL, " \t\n");
			output_file_mode = O_WRONLY | O_CREAT | O_TRUNC;
		}
		else if (_strcmp(token, ">>") == 0)
		{
			append_redirect = 1;
			output_file = _strtok(NULL, " \t\n");
			output_file_mode = O_WRONLY | O_CREAT | O_APPEND;
		}
		else
		{
			args[arg_count++] = token;
		}

		token = _strtok(NULL, " \t\n");
	}
	args[arg_count] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (input_redirect)
		{
			int input_fd = open(input_file, O_RDONLY);
			_dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		else if (input_fd != STDIN_FILENO)
		{
			_dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_redirect)
		{
			int output_fd = open(output_file, output_file_mode, 0666);
			_dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		if (append_redirect)
		{
			int output_fd = open(output_file, output_file_mode, 0666);
			_dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}

		_execvp(args[0], args);

		perror("_execvp");
		exit(1);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			return (-1);
		}
	}
	else
	{
		perror("fork");
		return (-1);
	}
}
/**
 *
 *
 *
 */
void execute_script(const char *script_file)
{
	int pipefd[2];
	char *pipe_symbol;
	int file = open(script_file, O_RDONLY);
	char line[MAX_LINE_LENGTH];
	int input_fd = STDIN_FILENO;
	int exit_status = 0;

	if (file == -1)
	{
		perror("open");
		return;
	}

	while (read(file, line, sizeof(line)) > 0)
	{
		line[_strcspn(line, "\n")] = '\0';

		if (_strlen(line) == 0 || line[0] == '#')
		{
			continue;
		}
		pipe_symbol = _strchr(line, '|');
		if (pipe_symbol)
		{
			*pipe_symbol = '\0';

			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				break;
			}
			exit_status = execute_cmd(line, input_fd);
			close(pipefd[1]);
			if (exit_status != 0)
			{
				print_err("Error executing command: %s\n", line);
				print_err("Exit status: %d\n", exit_status);
				break;
			}
			input_fd = pipefd[0];
			continue;
		}
		exit_status = execute_cmd(line, input_fd);
		if (exit_status != 0)
		{
			print_err("Error executing command: %s\n", line);
			print_err("Error status: %d\n", exit_status);
			break;
		}
		input_fd = STDIN_FILENO;
	}
	close(file);
}
/*
int execute_pipeline(char *commands[], int num_commands)
{
	int pipefds[MAX_CMDS -1][2];
	int i;

	for (i = 0; i < num_commands -1; i++)
	{
		if (pipe(pipefds[i]) < 0)
		{
			perror("pipe");
			return (-1);
		}
	}

	for (i = 0; i < num_commands; i++)
	{
		int input_fd = (i == 0) ? STDIN_FILENO : pipefds[i - 1][0];
		int output_fd = (i == num_commands - 1) ? STDOUT_FILENO : pipefds[i][1];

		int result = execute_cmd(commands[i], input_fd, output_fd);
		if (result < 0)
		{
			return (-1);
		}
	}

	for (i = 0; i < num_commands - 1; i++)
	{
		close(pipefds[i][0]);
		close(pipefds[i][1]);
	}
	return (0);
}
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		print_err("usage: %s script_file\n", argv[0]);
		return (1);
	}

	execute_script(argv[1]);
	return (0);
}*/
