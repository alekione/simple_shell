#include "main.h"

/**
 * createargv - is used to create character pointer array, for execve() method
 *	that is used to run commands.
 *	Since in main, the number of arguments passed is already given, so
 *	we pass it as argc in this function.
 *	On interactive shell the number of passed args is not determined unless
 *	it's calculated manually here.
 * @argc: argv counter as given from the main function
 * @argv: arguments passed to the function, from the main and a NULL
 *	pointer from interactive shell
 * @str: string holding the passed arguments, the main function passes NULL
 *	while interactive shell passes argument from the user
 * @source: is used to put the difference between arguments from
 *	the main() or other methods.
 *@delim: delimeter to use for separating string
 *	It manupulates the pointers to pointer arrays.
 */
void createargv(int argc, char *argv[], char *str, char source[], char delim)
{
	char *word_ptr,  word[50], main[] = "main", chr;
	int i = 0, count = 0, ind = 0, len;

	if (strcmp(source, main) == 0)
	{
		for (i = 1; i < argc; i++)
			*(argv + (i - 1)) = argv[i];
		*(argv + (argc - 1)) = NULL;
	}
	else
	{
		if (str == NULL)
		{
			*(argv + 0) = NULL;
			return;
		}
		len = strlen(str);
		while (i <= len)
		{
			chr = str[i];
			if ((chr == delim || chr == '\0') && ind > 0)
			{
				word[ind] = '\0';
				word_ptr = strdup(word);
				*(argv + count) = word_ptr;
				ind = 0;
				count++;
			}
			if (chr != delim)
			{
				word[ind] = chr;
				ind++;
			}
			i++;
		}
		*(argv + count) = NULL;
	}
}

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
		exit(60);
	else if (isexecutable(argv[0]))
		execute_command(argv, env);
	else
		perror(getenv("ERR_MSG"));
	return (-1);
}

/**
 * process_multiple - executes multiple commands in order given
 * @argv: array of pinter commands
 * @env: enviroment variables
 */
void process_multiple(char *argv[], char *env[])
{
	char *str, *arg[10], *iden[] = {";", "||", "&&"};
	int i = 0, j, k, start = 0, ind, res = 0, wstatus;
	pid_t cpid;

	while (true)
	{
		for (j = 0; j < 3; j++)
		{
			if (strcmp(argv[i], iden[j]) == 0 || argv[i] == NULL)
			{
				ind = 0;
				for (k = start; k < i; k++)
				{
					arg[ind] = argv[k];
					ind++;
				}
				arg[ind] = NULL;
				if (((str = iscommand(arg[0], getenv("PATH"))) == NULL &&
					!(isexecutable(arg[0]))) || (str != NULL &&
					!(isexecutable(str))))
				{
					perror(getenv("ERR_MSG"));
					exit(EXIT_FAILURE);
				}
				if (str != NULL && isexecutable(str))
					arg[0] = str;
				if ((cpid = fork()) == -1)
				{
					perror("fork");
					 return;
				}
				if (cpid == 0)
				{
					if (str == NULL)
						res = process_other(arg, env);
					else
						res = execute_command(arg, env);
					_exit(cpid);
				}
				waitpid(cpid, &wstatus, 0);
				if (res == -1 && j == 2)
					exit (EXIT_FAILURE);
				if (res == 0 && j == 1)
					exit(EXIT_SUCCESS);
				start = i + 1;
			}
		}
		if (argv[i] == NULL)
			break;
		i++;
	}
}
