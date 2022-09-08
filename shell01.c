#include "main.h"

/**
 * main - entry point of simple shell program
 * All function calls start in this function
 * @argc: argv counter
 * @argv: arguments passed to the function/program
 * Return: 0 for success
 */
int main(int argc, char *argv[])
{
	char *str;
	int ret, i;
	/**
	 *  if there is only one argument passed,
	 * the program should enter into interactive mode
	 * else, get argument number and determine the method to use
	 */
	if (argc == 1)
	{
		interactive();
		return (0);
	}
	for (i = 1; argv[i] != NULL; i++)
		*(argv + (i - 1)) = argv[i];
	*(argv + (argc - 1)) = NULL;
	str = argv[0];
	iscommand(&str, getenv("PATH"));
	if (str == NULL && isreadable(argv[0]))
	{
		ret = process_file(argv[0]);
		return (ret);
	}
	if (str != NULL && !(isexecutable(str)))
	{
		perror(getenv("ERR_MSG"));
		free(str);
		return (EXIT_FAILURE);
	}
	if (str != NULL && isexecutable(str))
		argv[0] = str;
	if (str == NULL)
		process_other(argv);
	else if (str != NULL && ismore_than_onecommand(argv))
		process_multiple(argv);
	else if (str != NULL && !(ismore_than_onecommand(argv)))
		execute_command(argv);
	return (EXIT_SUCCESS);
}

/**
 * interactive - the interactive section is controlled by this function.
 * Works like a shell inside a shell i.e.,
 * it creates its own prompt and execute commands passed into it
 * It does not return anything
 */
void interactive(void)
{
	char *str, *ptr = NULL, prompt[] = "$ ", *exarg[20];
	size_t size = 0;
	ssize_t ret;

	while (true)
	{
		ptr = NULL;
		write(1, &prompt, 2);
		ret = getline(&ptr, &size, stdin);
		if (ret == -1)
			exit(errno);
		stripstr(&ptr);
		if (ptr == NULL)
		{
			free(ptr);
			continue;
		}
		/* i found that getline method, is adding '\n'  char at the end  */
		createargv(exarg, ptr, ' ');
		free(ptr);
		str = exarg[0];
		iscommand(&str, getenv("PATH"));
		if (str == NULL && isreadable(exarg[0]))
		{
			process_file(exarg[0]);
			_free(exarg, &str);
			continue;
		}
		if (str != NULL && !(isexecutable(str)))
		{
			perror(getenv("ERR_MSG"));
			_free(exarg, &str);
			continue;
		}
		interactive2(exarg, str);
	}
}

/**
 * interactive2 - continue interactive function
 * @exarg: arguments commands
 * @str: string for comparison
 */
void interactive2(char *exarg[], char *str)
{
	if (str != NULL && isexecutable(str))
	{
		free(exarg[0]);
		exarg[0] = str;
	}

	if (str == NULL)
		process_other(exarg);
	else if (ismore_than_onecommand(exarg))
		process_multiple(exarg);
	else if (!(ismore_than_onecommand(exarg)))
		execute_command(exarg);
}

/**
 * execute_command - executes a given command
 * @argv: array of command pointers
 * Return: -1 in failure, nothing or zero 0n success
 */
int execute_command(char *argv[])
{
	int wstatus;
	pid_t cpid;

	process_dollar_sign(argv);
	setenv("EXT_VAL", "0", 1);
	cpid = fork();
	if (cpid == -1)
	{
		perror(getenv("ERR_MSG"));
		return (EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		execve(argv[0], argv, environ);
		setenv("EXT_VAL", num_tostring(errno), 1);
		perror(getenv("ERR_MSG"));
		exit(EXIT_FAILURE);
	}
	waitpid(cpid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	setenv("EXT_VAL", num_tostring(errno), 1);
	return (EXIT_SUCCESS);
}

/**
 * _free - frees a memory
 * @argv: pointer arrays
 * @str: string pointers
 */
void _free(char *argv[], char **str)
{
	int i = 0;

	free(*str);
	while (*(argv + i) != NULL)
	{
		free(*(argv + i));
		i++;
	}
}
