#include "main.h"

/**
 * main - entry point of simple shell program
 * All function calls start in this function
 * @argc: argv counter
 * @argv: arguments passed to the function/program
 * @env: enviroment/global variables to the program
 * Return: 0 for success
 */
int main(int argc, char *argv[])
{
	char *str;
	int ret;
	/**
	 *  if there is only one argument passed,
	 * the program should enter into interactive mode
	 * else, get argument number and determine the method to use
	 */
	setenv("ERR_MSG", argv[0], 1);
	if (argc == 1)
	{
		interactive();
		return (0);
	}
	createargv(argc, argv, NULL, "main", ' ');
	if (isreadable(argv[0]))
	{
		ret = process_file(argv[0]);
		return (ret);
	}
	str = iscommand(argv[0], getenv("PATH"));
	if (str != NULL && isexecutable(str))
		argv[0] = str;
	if (str != NULL && !(isexecutable(str)))
	{
		perror(getenv("ERR_MSG"));
		return (EXIT_FAILURE);
	}
	if (str == NULL)
		process_other(argv);
	else if (str != NULL && ismore_than_onecommand(argv))
		process_multiple(argv);
	else if (str != NULL && !(ismore_than_onecommand(argv)))
		execute_command(argv);
	free(str);
	return (EXIT_SUCCESS);
}

/**
 * interactive - the interactive section is controlled by this function.
 * Works like a shell inside a shell i.e.,
 * it creates its own prompt and execute commands passed into it
 * @env: pointer arrays holding enviroment/global values
 * It does not return anything
 */
void interactive(void)
{
	char *str, *ptr, prompt[] = " ($)", *exarg[20];
	size_t size = 0;

	while (true)
	{
		ptr = NULL;
		write(1, &prompt, 4);
		getline(&ptr, &size, stdin);
		/**
		 * i found that getline method, is adding '\n'  char at the end
		 * the char is causing the program to give unexpected results,
		 * so it has to be stripped before continuing with the program.
		 */
		createargv(0, exarg, stripstr(ptr), "interactive", ' ');
		if (isreadable(exarg[0]) )
		{
			process_file(exarg[0]);
			free(ptr);
			continue;
		}
		str = iscommand(exarg[0], getenv("PATH"));
		if (str != NULL && !(isexecutable(str)))
		{
			perror(getenv("ERR_MSG"));
			free(ptr);
			continue;
		}
		if (str != NULL && isexecutable(str))
			exarg[0] = str;
		if (str == NULL)
			process_other(exarg);
		else if (ismore_than_onecommand(exarg))
			process_multiple(exarg);
		else if(!(ismore_than_onecommand(exarg)))
			execute_command(exarg);
		free(ptr);
		free(str);
	}
}

/**
 * execute_command - executes a given command
 * @argv: array of command pointers
 * @env: enviroment variables
 * Return: -1 in failure, nothing or zero 0n success
 */
int execute_command(char *argv[])
{
	int wstatus;
	pid_t cpid;
	extern char **environ;

	process_dollar_sign(argv);
	setenv("EXT_VAL", "0", 1);
	if ((cpid = fork()) == -1)
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
