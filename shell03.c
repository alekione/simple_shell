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

void free_argv2(command *cmd)
{
	int i;
	
	for (i = 0; i < 50; i++)
		free(cmd->argv2[i]);
	cmd->argv2 = malloc(50 * sizeof(char *));
	if (cmd->argv2 == NULL)
	{
		perror(cmd->p_name);
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < 50; i++)
		cmd->argv2[i] = NULL;
}
/**
 * free_hist - frees the memory of pointers
 */
void free_half(command *cmd)
{
	int i;

	for (i = 0; i < ARR_SIZE; i++)
	{
		free(cmd->argv1[i]);
		cmd->argv1[i] = NULL;
	}
	for (i = 0; i < 50; i++)
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
