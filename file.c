#include "main.h"

/**
 * process_file - processes a given command file
 * @file: file passed
 * Return: 0 on success
 */
int process_file(char *file)
{
	char *ptr = NULL, *argv[20];
	size_t size = 0;
	ssize_t rd;
	FILE *op;
	int ret;

	op = fopen(file, "r");
	if (op == NULL)
	{
		perror(getenv("ERR_MSG"));
		setenv("EXT_VAL", num_tostring(errno), 1);
		return (EXIT_FAILURE);
	}
	while (true)
	{
		rd = getline(&ptr, &size, op);
		if (rd == -1 || rd == 0)
			break;
		stripstr(&ptr);
		createargv(argv, ptr, ' ');
		ret = process_file2(argv);
		if (ret == EXIT_FAILURE)
		{
			_free(argv, &ptr);
			fclose(op);
			return (EXIT_FAILURE);
		}
	}
	fclose(op);
	_free(argv, &ptr);
	return (EXIT_SUCCESS);
}

/**
 * process_file2 - continues process_file function
 * @argv: array of commands
 * Return: 0 on success
 */
int process_file2(char *argv[])
{
	int ret;
	char *str = NULL;

	if (ismore_than_onecommand(argv))
		ret = process_multiple(argv);
	else
	{
		str = argv[0];
		iscommand(&str, getenv("PATH"));
		if (str != NULL && !(isexecutable(str)))
		{
			perror(getenv("ERR_MSG"));
			return (EXIT_FAILURE);
		}
		if (str != NULL && isexecutable(str))
		{
			argv[0] = str;
			ret = execute_command(argv);
		}
		if (str == NULL)
			ret = process_other(argv);
	}
	free(str);
	return (ret);
}
