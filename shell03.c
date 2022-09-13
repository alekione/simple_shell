#include "main.h"

/**
 * on_exit - exits the program
 * @num: exit value
 */
void is_exit(int num, command *cmd)
{
	free_onexit(cmd);
	exit(num);
}

/**
 * free_str - free memory of a given string
 * @str: pointer to tstring location
 */
void free_str(char **str)
{
	free(*str);
	*str = NULL;
}

/**
 * free_argv2 - frees argv2 array
 * @cmd: command struct data type
 */
void free_argv(char **argv)
{
	int i;
	
	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
		argv[i] = NULL;
	}
}
/**
 * free_hist - frees the memory of pointers
 */
void free_half(command *cmd)
{
	int i;

	for (i = 0; cmd->argv1[i] != NULL; i++)
	{
		free(cmd->argv1[i]);
		cmd->argv1[i] = NULL;
	}
	for (i = 0; cmd->argv2[i] != NULL; i++)
	{
		free(cmd->argv2[i]);
		cmd->argv2[i] = NULL;
	}
}

/**
 * free_hist_end - frees memory at the end of the function
 */
void free_onexit(command *cmd)
{
	int i;

	for (i = 0; i < ARR_SIZE; i++)
	{
		free(cmd->env[i]);
		free(cmd->argv1[i]);
	}
	for (i = 0; i < 50; i++)
		free(cmd->argv2[i]);
}
