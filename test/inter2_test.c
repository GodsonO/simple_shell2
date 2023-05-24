#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glob.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdbool.h>

int is_builtin_command(const char* command) {
    // List of built-in commands
    const char* builtins[] = {"cd", "help", "exit"};
    int num_builtins = sizeof(builtins) / sizeof(char*);
    
    for (int i = 0; i < num_builtins; ++i) {
        if (strcmp(command, builtins[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

void execute_builtin_command(const char* command, char** arguments) {
    if (strcmp(command, "cd") == 0) {
        /*if (num_arguments != 2) {
            printf("cd: Invalid number of arguments\n");
            return;
        }*/
	if (arguments[1] == NULL)
	{
		printf("cd: directory argument missing\n");
	}
	else if (arguments[2] != NULL)
	{
		printf("cd: invalid number of arguments\n");
	}
	else
	{
        	if (chdir(arguments[1]) != 0) {
            	printf("cd: Directory change failed\n");
        }
	}
    } else if (strcmp(command, "help") == 0) {
        printf("Help command executed\n");
        // Add your help implementation here
    } else if (strcmp(command, "exit") == 0) {
        exit(0);
    } else {
	    printf("Unknown command: %s\n", command);
    }
}

void execute_external_command(const char* command, char** arguments) {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        if (execvp(command, arguments) == -1) {
            printf("Error executing the command '%s'\n", command);
            exit(1);
        }
    } else if (pid < 0) {
        // Error forking process
        printf("Error forking process\n");
    } else {
        // Parent process
        wait(NULL);
    }
}


void free_arguments(char** arguments) {
    for (int i = 0; arguments[i] != NULL; ++i) {
        free(arguments[i]);
    }
}
int wildcard_match(const char* pattern, const char* string) {
    while (*pattern) {
        if (*pattern == '*') {
            if (wildcard_match(pattern + 1, string))
                return 1;
            if (*string && wildcard_match(pattern, string + 1))
                return 1;
            return 0;
        } else if (*pattern == *string || *pattern == '?') {
            pattern++;
            string++;
        } else {
            return 0;
        }
    }

    return *string == '\0';
}

void tokenize_arguments(char* cmdline, char** arguments, int max_arguments) {
    int i = 0;
    char* token = strtok(cmdline, " \t\n");

    while (token != NULL && i < max_arguments - 1) {
        arguments[i++] = token;
        token = strtok(NULL, " \t\n");
    }

    arguments[i] = NULL;
}

bool fnmatch_match(const char* pattern, const char* string) {
    while (*pattern) {
        if (*pattern == '*') {
            if (fnmatch_match(pattern + 1, string))
                return true;
            if (*string && fnmatch_match(pattern, string + 1))
                return true;
            return false;
        } else if (*pattern == '?' || *pattern == *string) {
            pattern++;
            string++;
        } else {
            return false;
        }
    }

    return (*string == '\0');
}

bool fnmatch(const char* pattern, const char* string) {
    return fnmatch_match(pattern, string);
}


void expand_wildcards(char** arguments) {
    const int max_arguments = 256;
    char* expanded_arguments[max_arguments];

    int i = 0;
    while (arguments[i] != NULL) {
        char* argument = arguments[i];
        int num_matches = 0;

        if (strpbrk(argument, "*?") != NULL) {
            // Wildcard found, perform expansion
            DIR* dir = opendir(".");
            if (dir) {
                struct dirent* entry;

                while ((entry = readdir(dir)) != NULL) {
                    if (wildcard_match(argument, entry->d_name)) {
                        // Match found, add it to the expanded arguments
                        expanded_arguments[num_matches++] = strdup(entry->d_name);
                    }
                }

                closedir(dir);
            }
        } else {
            // Non-wildcard argument, add it as-is
            expanded_arguments[num_matches++] = argument;
        }

        // Move to the next argument
        i++;
    }

    // Terminate the expanded arguments array
    expanded_arguments[i] = NULL;

    // Copy the expanded arguments back to the original arguments array
    for (int j = 0; expanded_arguments[j] != NULL; j++) {
        arguments[j] = expanded_arguments[j];
    }
    arguments[i] = NULL;
}

void handle_command(const char* command_line) {
    const int max_cmdline_length = 256;
    char command_line_copy[max_cmdline_length];

    strcpy(command_line_copy, command_line);

    // Remove trailing newline character
    command_line_copy[strcspn(command_line_copy, "\n")] = '\0';

    // Tokenize command line
    char* arguments[max_cmdline_length];
    tokenize_arguments(command_line_copy, arguments, max_cmdline_length);

    if (arguments[0] == NULL) {
        // Empty command line
        return;
    }

    expand_wildcards(arguments);

    const char* command = arguments[0];

    if (is_builtin_command(command)) {
        // Execute built-in command
        execute_builtin_command(command, arguments);
        free_arguments(arguments);
    } else {
        // Execute external command
        execute_external_command(command, arguments);
        free_arguments(arguments);
    }
}

int main() {
    const int max_cmdline_length = 256;
    char command_line[max_cmdline_length];

    while (1) {
        printf(">> ");
        fgets(command_line, sizeof(command_line), stdin);

        // Remove trailing newline character
        command_line[strcspn(command_line, "\n")] = '\0';

        // Tokenize command line
        char* arguments[max_cmdline_length];
        tokenize_arguments(command_line, arguments, max_cmdline_length);

        if (arguments[0] == NULL) {
            // Empty command line
            continue;
        }

        expand_wildcards(arguments);

        const char* command = arguments[0];

        if (is_builtin_command(command)) {
            // Execute built-in command
            execute_builtin_command(command, arguments);
        } else {
            // Execute external command
            execute_external_command(command, arguments);
        }

        free_arguments(arguments);
    }

    return 0;
}
