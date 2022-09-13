#include "main.h"

/**
 * process_multiple - processes multiple commands
 */
int process_multiple(char *argv[], command *cmd)
{
	int i = 0, j, k, start = 0, ind, ret;
	char *str, *iden[] = {"||", "&&", ";"};
	char *arr[50];

	while (true)
	{
		str = argv[i];
		for (j = 0; j < 3; j++)
		{
			if (str == NULL || _strcmp(iden[j], str) == 0)
			{
				ind = 0;
				for (k = start; k < i; k++, ind++)
					arr[ind] = argv[k];
				arr[ind] = NULL;
				ret = process_multiple2(arr, cmd);
				if (ret == EXIT_FAILURE && j == 1)
					return (EXIT_FAILURE);
				if (ret == EXIT_SUCCESS && j == 0)
					return (EXIT_SUCCESS);
				start = i + 1;
				break;
			}
		}
		if (str == NULL)
			break;
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * process_multiple2 - continues process_multiple
 * @argv: command array
 * Return: success or failure
 */
int process_multiple2(char *argv[], command *cmd)
{
	int ret = 0;

	if (isreadable(argv[0]) && !(iscommand(&argv[0], cmd)))
		ret = process_file(argv[0], cmd);
	else if (iscommand(&argv[0], cmd))
		ret = execute_command(argv, cmd);
	else 
		ret = execute_custom(argv, cmd);
	if (ret == EXIT_SUCCESS)
		errno = 0;
	return (ret);
}
