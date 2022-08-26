#include "main.h"

/**
 * isexit - used to ckeck whether the passed command is exit command
 * @str: Array of character pointers
 */
bool isexit(char *str[])
{
	int i = 0;

	while(str[i] != NULL)
	{
		if (strcmp(str[i], "exit") == 0)
		{
			if (str[i + 1] == NULL)
				exit(0);
			else
				exit (atoi(str[i + 1]));
		}
		i++;
	}
	return (false);
}
