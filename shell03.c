#include "main.h"

/**
 * createargv - is used to create character pointer array, for execve() method
 *	that is used to run commands.
 *	Since in main, the number of arguments passed is already given, so
 *	we pass it as argc in this function.
 *	On interactive shell the number of passed args is not determined unless
 *	it's calculated manually here.
 * @*argv: arguments passed to the function, from the main and a NULL
 *	pointer from interactive shell
 * @str: string holding the passed arguments, the main function passes NULL
 *	while interactive shell passes argument from the user
 * @delim: delimeter to use for separating string
 *	It manupulates the pointers to pointer arrays.
 */
void createargv(char *(*argv)[], char *str, char delim)
{
	char word[50], chr;
	int i = 0, count = 0, ind = 0, len;

	if (str == NULL)
	{
		*(*argv + 0) = NULL;
		return;
	}
	len = strlen(str);
	while (i <= len)
	{
		chr = str[i];
		if ((chr == delim || chr == '\0' || chr == '#') && ind > 0)
		{
			word[ind] = '\0';
			*(*argv + count) = strdup(word);
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
	*(*argv + count) = NULL;
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
 * Return: 0 for success
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
				str = arg[0];
				iscommand(&str, getenv("PATH"));
				if (str != NULL && !(isexecutable(str)))
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
				free(str);
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

/**
 * _free2 - free a memory
 * @argv: array of pointers
 * @str: string pointer
 */
void _free2(char ***argv, char **str)
{
	int i = 0;

	free(*str);
	while (*(*argv + i) != NULL)
	{
		free((*argv[i]));
		i++;
	}
}
