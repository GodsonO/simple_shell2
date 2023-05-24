#include "shell.h"

/**
 *
 */
int match_wildcards(const char *pattern, const char *string)
{
	while (*pattern != '\0' || *string != '\0')
	{
		if (*pattern == '*')
		{
			pattern++;

			if (*pattern == '\0')
			{
				return (1);
			}

			while (
