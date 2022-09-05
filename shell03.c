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
	char *ptr, word[50], main[] = "main", chr;
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
			if ((chr == delim || chr == '\0' || chr == '#') && ind > 0)
			{
				word[ind] = '\0';
				ptr = strdup(word);
				*(argv + count) = ptr;
				ind = 0;
				count++;
			}
			if (chr != delim)
			{
				word[ind] = chr;
				ind++;
			}
			if (chr == '#')
				break;
			i++;
		}
		*(argv + count) = NULL;
		free((ptr = NULL));
	}
}

/**
 * process_other - executes other commands - custom commands
 * @argv: array of commands 
 * Return: -1 incase of failure 0 on success
 */
int process_other(char *argv[])
{
	char *set = "setenv", *unset = "unsetenv", *exitc = "exit";
	char *cdir = "cd";

	if (ismore_than_onecommand(argv))
	{
		process_multiple(argv);
		return (EXIT_SUCCESS);
	}
	if (strcmp(argv[0], set) == 0 || strcmp(argv[0], unset) == 0)
		return (processenv(argv));
	else if (strcmp(argv[0], cdir) == 0)
		return (cd(argv[1]));
	else if (strcmp(argv[0], exitc) == 0)
	{
		if (argv[1] != NULL)
			exit(atoi(argv[1]));
		exit(EXIT_SUCCESS);
	}
	else
		return (execute_command(argv));
}

/**
 * process_multiple - executes multiple commands in order given
 * @argv: array of pinter commands
 */
int process_multiple(char *argv[])
{
	char *str, *arg[10], *iden[] = {";", "||", "&&"};
	int i = 0, j, k, start = 0, ind, res;

	while (true)
	{
		for (j = 0; j < 3; j++)
		{
			if (argv[i] == NULL || strcmp(argv[i], iden[j]) == 0)
			{
				ind = 0;
				for (k = start; k < i; k++)
				{
					arg[ind] = argv[k];
					ind++;
				}
				arg[ind] = NULL;
				if (((str = iscommand(arg[0], getenv("PATH"))) != NULL &&
					!(isexecutable(str))))
				{
					perror(getenv("ERR_MSG"));
					return (EXIT_FAILURE);
				}
				if (str != NULL && isexecutable(str))
					arg[0] = str;
				res = complete_process_multiple(arg, str);
				if (res == EXIT_FAILURE && j == 2)
					return (EXIT_FAILURE);
				if (res == EXIT_SUCCESS && j == 1)
					return (EXIT_SUCCESS);
				start = i + 1;
				break;
			}
		}
		if (argv[i] == NULL)
			break;
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * complete_process_multiple - complete the process-multiple function
 * @argv: command arguments
 * @str: string for comparison
 * Return: -1 on error 0 on success
 */
int complete_process_multiple(char *argv[], char *str)
{
	if (str == NULL)
		return (process_other(argv));
	else
		return (execute_command(argv));
}
