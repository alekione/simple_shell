#include "main.h"

/**
 * process_multiple - processes multiple commands
 */
int process_multiple(char *argv[], command *cmd)
{
	int i = 0, j, k, start = 0, ind, ret;
	char *str, *iden[] = {"||", "&&", ";"};
	bool isdone = false;

	print('e', __FILE__, __func__);
	while (true)
	{
		str = argv[i];
		for (j = 0; j < 3; j++)
		{
			if (_strcmp(iden[j], str) == 0 || str == NULL)
			{
				ind = 0;
				for (k = start; k < i; k++, ind++)
					cmd->argv2[ind] = argv[k];
				cmd->argv2[ind] = NULL;
				ret = process_multiple2(cmd);
				if (ret == EXIT_FAILURE && j == 1)
				{
					print('r', __FILE__, __func__);
					return (EXIT_FAILURE);
				}
				if (ret == EXIT_SUCCESS && j == 0)
				{	
					print('r', __FILE__, __func__);
					return (EXIT_SUCCESS);
				}
				if (isdone)
					break;
				start = i + 1;
			}
		}
		if (str == NULL || isdone)
			break;
	}
	print('e', __FILE__, __func__);
	return (EXIT_SUCCESS);
}

/**
 * process_multiple2 - continues process_multiple
 * @argv: command array
 * Return: success or failure
 */
int process_multiple2(command *cmd)
{
	int ret = 0;

	if (isreadable(cmd->argv2[0]) && !(iscommand(&cmd->argv2[0], cmd)))
		ret = process_file(cmd->argv2[0], cmd);
	else if (iscommand(&cmd->argv2[0], cmd))
		ret = execute_command(cmd->argv2, cmd);
	else 
		ret = execute_custom(cmd->argv2, cmd);
	if (ret == EXIT_SUCCESS)
		errno = 0;
	return (ret);
}
