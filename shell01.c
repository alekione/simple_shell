#include "main.h"

/**
 * isexit - exits the program with passed exit value, if nonr,
 * 	exits with a zero.
 */
void isexit(char *argv[])
{
	char *ext = "exit";
	int i = 0;

	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], ext) == 0)
		{
			if (argv[i++] != NULL)
				exit(atoi(argv[i]++));
			exit(0);
		}
		i++;
	}
}

/**
 * main - entry point of simple shell program
 * All function calls start in this function
 * @argc: argv counter
 * @argv: arguments passed to the function/program
 * @env: enviroment/global variables to the program
 * Return: 0 for success
 */
int main(int argc, char *argv[],
		char *env[])
{
	char *str, *chr;
	/**
	 *  if there is only one argument passed,
	 * the program should enter into interactive mode
	 * else, get argument number and determine the method to use
	 */
	if (argc == 1)
	{
		interactive(env);
		return (0);
	}
	chr = argv[1];
	createargv(argc, argv, NULL, "main", ' ');
	str = iscommand(argv[0], getenv("PATH"));
	if (str != NULL && isexecutable(str))
		argv[0] = str;
	if (str != NULL && !(isexecutable(str)))
	{
		perror(chr);
		return (EXIT_FAILURE);
	}
	if (str == NULL)
		process_other(argv, env);
	else if (str != NULL && ismore_than_onecommand(argv))
		process_multiple(argv, env);
	else if (str != NULL && !(ismore_than_onecommand(argv)))
		execute_command(argv, env);
	return (EXIT_SUCCESS);
}

/**
 * interactive - the interactive section is controlled by this function.
 * Works like a shell inside a shell i.e.,
 * it creates its own prompt and execute commands passed into it
 * @env: pointer arrays holding enviroment/global values
 * It does not return anything
 */
void interactive(char *env[])
{
	char *str, *ptr = NULL, prompt[] = " ($)", *exarg[20];
	pid_t session;
	size_t size = 0;
	int wstatus;

	while (true)
	{
		write(1, &prompt, 4);
		getline(&ptr, &size, stdin);
		/**
		 * i found that getline method, is adding '\n'  char at the end
		 * the char is causing the program to give unexpected results,
		 * so it has to be stripped before continuing with the program.
		 */
		createargv(0, exarg, stripstr(ptr), "interactive", ' ');
		str = iscommand(exarg[0], getenv("PATH"));
		if (str != NULL && !(isexecutable(str)))
		{
			perror(exarg[0]);
			continue;
		}
		if (str != NULL && isexecutable(str))
			exarg[0] = str;
		session = fork();
		if (session == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (session == 0)
		{
			if (str == NULL)
				process_other(exarg, env);
			else if (ismore_than_onecommand(exarg))
				process_multiple(exarg, env);
			else if(!(ismore_than_onecommand(exarg)))
				execute_command(exarg, env);
		}
		waitpid(session, &wstatus, 0);
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 60)
			isexit(exarg);
	}
	free(ptr);
}

/**
 * execute_command - executes a given command
 * @argv: array of command pointers
 * @env: enviroment variables
 * Return: -1 in failure, nothing or zero 0n success
 */
int execute_command(char *argv[], char *env[])
{
	char *str;

	str = iscommand(argv[0], getenv("PATH"));
	if (str == NULL)
		return (process_other(argv, env));
	argv[0] = str;
	execve(argv[0], argv, env);
	perror("execve");
	return (-1);
}
