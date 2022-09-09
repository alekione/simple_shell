#include "main.h"

/**
 * on_exit - exits the program
 * @num: exit value
 */
void is_exit(int num, command *cmd)
{
	free_hist_end(cmd);
	exit(num);
}

/**
 * free_hist - frees the memory of pointers
 */
void free_hist(command *cmd)
{
	int i = 0;
	char *list[ARR_SIZE];

	while(cmd->list[i] != NULL)
	{
		free(cmd->list[i]);
		cmd->list[i] = NULL;
		i++;
	}
	cmd->hist_count = 0;
	cmd->max_count = ARR_SIZE;
	cmd->list = list;
	for (i = 0; i < ARR_SIZE; i++)
		cmd->list[i] = NULL;
}

/**
 * free_hist_end - frees memory at the end of the function
 */
void free_hist_end(command *cmd)
{
	int i = 0;

	while (cmd->list[i] != NULL)
	{
		free(cmd->list[i]);
		i++;
	}
}
