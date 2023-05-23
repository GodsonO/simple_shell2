#include "shell.h"

typedef struct {
    int num_arg;
    char **arguments;
} commnd;

int match(const char *pattern, const char *text);
char **expand(const char *pattern);
int arg(commnd *cmd);

int main() {
    commnd cmd;
    cmd.num_arg = 3;
    cmd.arguments = malloc(cmd.num_arg * sizeof(char*));
    cmd.arguments[0] = strdup("file*.txt");
    cmd.arguments[1] = strdup("test?.doc");
    cmd.arguments[2] = strdup("image.jpg");

    arg(&cmd);

    // Clean up
    for (int i = 0; i < cmd.num_arg; i++) {
        free(cmd.arguments[i]);
    }
    free(cmd.arguments);

    return 0;
}

int arg(commnd *cmd) {
    int k, j, i, n;
    int count = 0;
    int wildcard = 0;


    for (k = 0; k < cmd->num_arg; k++) {
        if (strpbrk(cmd->arguments[k], "*?[]{}") != NULL) {
            wildcard = 1;
            break;
        }
    }


    if (wildcard) {
        j = 0; 
	while(j < cmd->num_arg)
	{
            char **exp_results = expand(cmd->arguments[j]);

            if (exp_results != NULL) {
		    count = 0;
		    for (n = 0; exp_results[n] != NULL; n++)
		    {
			    count++;
		    }
    		cmd->arguments = realloc(cmd->arguments, (cmd->num_arg + count) * sizeof(char *));
                    for (int i = 0; exp_results[i] != NULL; i++) {
			cmd->arguments[cmd->num_arg + i] = strdup(exp_results[i]);
                    printf("Expanded result %d: %s\n", i + 1, exp_results[i]);
                    free(exp_results[i]);
                }
		cmd->num_arg += count;
                free(exp_results);

		j++;
            }
	    else{
	    j++;
	    }
        }
    
   }
    return (0);
}

int match(const char *pattern, const char *text) {
    if (*pattern == '\0' && *text == '\0') {
        return 1;
    }

    if (*pattern == '*' && *(pattern + 1) != '\0' && *text == '\0') {
        return 0;
    }

    if (*pattern == '?' || *pattern == *text) {
        return match(pattern + 1, text + 1);
    }

    if (*pattern == '*') {
        return match(pattern + 1, text) || match(pattern, text + 1);
    }

    return 0;
}

char **expand(const char *pattern) {
    DIR *dir;
    struct dirent *entry;
    size_t prefixlen;
    char *prefix = NULL;
    char *suffix = NULL;
    char **results = NULL; // Stores expanded results
    int result_count = 0; // Keeps track of the number of expanded results

    char *asterisk = strchr(pattern, '*');
    if (asterisk != NULL) {
        prefixlen = asterisk - pattern;
        prefix = malloc((prefixlen + 1) * sizeof(char));
        strncpy(prefix, pattern, prefixlen);
        prefix[prefixlen] = '\0';

        suffix = strdup(asterisk + 1);
    } else {
        prefix = strdup(pattern);
        suffix = malloc(sizeof(char));
        *suffix = '\0';
    }

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (match(prefix, entry->d_name) && match(suffix, entry->d_name + strlen(prefix))) {
            result_count++;
            char **temp = realloc(results, (result_count + 1) * sizeof(char*));
            if (temp == NULL) {
                perror("realloc");
                break;
            }
            results = temp;

            results[result_count - 1] = strdup(entry->d_name);
            results[result_count] = NULL;
        }
    }

    closedir(dir);
    free(prefix);
    free(suffix);

    return results;
}
