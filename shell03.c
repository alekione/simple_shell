#include "main.h"

/**
 * process_other - executes other commands - custom commands
 * @argv: array of commands 
 * @env: enviroment variables
 * Return: -1 incase of failure 0 on success
 */
int process_other(char *argv[], char *env[])
{
	char *set = "setenv", *unset = "unsetenv", *exitc = "exit", *cdir = "cd";

	if (ismore_than_onecommand(argv))
	{
		process_multiple(argv, env);
		return (EXIT_SUCCESS);
	}
	if (strcmp(argv[0], set) == 0 || strcmp(argv[0], unset) == 0)
		return (processenv(argv));
	else if (strcmp(argv[0], cdir) == 0)
		return (cd(argv));
	else if (strcmp(argv[0], exitc) == 0)
	{
		if (argv[1] != NULL)
			exit(atoi(argv[1]));
		exit(EXIT_SUCCESS);
	}
	else if (iscommand(argv[0], getenv("PATH")) == NULL)
	{
		perror(argv[0]);
		return (EXIT_FAILURE);
	}
	return (execute_command(argv, env));
}

/**
 * process_multiple - executes multiple commands in order given
 * @argv: array of pinter commands
 * @env: enviroment variables
 */
void process_multiple(char *argv[], char *env[])
{
	char *arg[10], *iden[] = {";", "||", "&&"};
	int i = 0, j, k, start = 0, ind, res = 0, wstatus;
	pid_t cpid;

	while (i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (argv[i] == iden[j] || argv[i] == NULL)
			{
				ind = 0;
				for (k = start; k < i; k++)
					arg[ind++] = argv[k];
				arg[ind] = NULL;
				cpid = fork();
				if (cpid == -1)
				{
					perror("fork");
					 return;
				}
				if (cpid == 0)
				{
					res = execute_command(arg, env);
					_exit(cpid);
				}
				waitpid(cpid, &wstatus, 0);
				if (res == -1 && j == 2)
					exit (EXIT_FAILURE);
				if (res != -1 && j == 1)
					exit(EXIT_SUCCESS);
				start = i + 1;
			}
			if (argv[i] == NULL)
				break;
		}
	}
}
