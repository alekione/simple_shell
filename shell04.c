#include "main.h"

/**
 * execute_command - executes a given command
 * @argv: array of command pointers
 * Return: -1 in failure, nothing or zero 0n success
 */
int execute_command(char *argv[], command *cmd)
{
	int wstatus;
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror(cmd->p_name);
		return (EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		execve(argv[0], argv, cmd->env);
		perror(cmd->p_name);
		exit(EXIT_FAILURE);
	}
	waitpid(cpid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_SUCCESS);
}

/**
 * execute_custom - executes the custom commands
 * @argv: array of command and arguments
 * Return: 0 on success
 */
int execute_custom(char *argv[], command *cmd)
{
	char *ext = "exit", *setenv = "setenv", *unset = "unsetenv",
		*chd = "cd", *chr;
	int i, ret;

	if (_strcmp(argv[1], ext) == 0)
	{
		if (argv[1] == NULL)
			is_exit(0, cmd);
		chr = argv[1];
		for (i = 0; chr[i] != '\0'; i++)
		{
			if (chr[i] > '9' || chr[i] < '0')
			{
				errno = EINVAL;
				perror(cmd->p_name);
				ret = EXIT_FAILURE;
			}
		}
		is_exit(atoi(chr), cmd);
	}
	else if (_strcmp(argv[0], setenv) == 0)
		ret = set_env(argv[1], argv[2], cmd);
	else if (_strcmp(argv[0], unset) == 0)
		ret = unset_env(argv[1], cmd);
	else if (_strcmp(argv[0], chd) == 0)
		ret = cd(argv, cmd);
	else
	{
		errno = 2;
		perror(cmd->p_name);
		return (EXIT_FAILURE);
	}
	return (ret);
}
