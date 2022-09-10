#include "main.h"

/**
 * process_file - processes a given command file
 * @file: file passed
 * Return: 0 on success
 */
int process_file(char *file, command *cmd)
{
	char *ptr = NULL, *argv[ARR_SIZE];
	size_t size = 0;
	ssize_t rd;
	FILE *op;
	int ret;

	print('e', __FILE__, __func__);
	op = fopen(file, "r");
	if (op == NULL)
	{
		perror(cmd->p_name);
		return (EXIT_FAILURE);
	}
	while (true)
	{
		rd = getline(&ptr, &size, op);
		if (rd == -1 || rd == 0)
			break;
		stripstr(&ptr);
		createargv(argv, ptr, ' ', cmd);
		ret = process_file2(argv, cmd);
		if (ret == EXIT_FAILURE)
		{
			fclose(op);
			return (EXIT_FAILURE);
		}
	}
	fclose(op);
	print('r', __FILE__, __func__);
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
