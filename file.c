#include "main.h"

/**
 * process_file - processes a given command file
 * @file: file passed
 * Return: 0 on success
 */
int process_file(char *file, command *cmd)
{
	char *ptr = NULL;
	size_t size = 0;
	ssize_t rd;
	FILE *op;
	int ret;

	op = fopen(file, "r");
	if (op == NULL)
	{
		perror(cmd->p_name);
		return (EXIT_FAILURE);
	}
	while (true)
	{
		free_argv(cmd->argv2);
		rd = getline(&ptr, &size, op);
		if (rd == -1 || rd == 0)
			break;
		stripstr(&ptr);
		createargv(cmd->argv2, ptr, ' ', cmd);
		ret = process_file2(cmd->argv2, cmd);
		if (ret == EXIT_FAILURE)
		{
			fclose(op);
			free_argv(cmd->argv2);
			return (EXIT_FAILURE);
		}
	}
	fclose(op);
	free_argv(cmd->argv2);
	return (EXIT_SUCCESS);
}

/**
 * process_file2 - continues process_file function
 * @argv: array of commands
 * Return: 0 on success
 */
int process_file2(char *argv[], command *cmd)
{
	int ret;

	if (ismultiple_command(argv))
		ret = process_multiple(argv, cmd);
	else
	{
		if (isreadable(argv[0]) && !(iscommand(&argv[0], cmd)))
			ret = process_file(argv[0], cmd);
		else if (iscommand(&argv[0], cmd))
			ret = execute_command(argv, cmd);
		else
			ret = execute_custom(argv, cmd);
	}
	return (ret);
}
