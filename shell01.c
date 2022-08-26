#include "main.h"

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
	char *str;
	/**
	 *  if there is only one argument passed,
	 * the program should enter into interactive mode
	 * else, get argument number and determine the method to use
	 */
	if (argc == 1)
		interactive(env);
	str = argv[1];
	createargv(argc, argv, NULL, "main", ' ');
	if (!(pathexist(argv[0])))
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
	execve(argv[0], argv, env);
	perror("execve");
	return (0);
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
		str = iscommand(exarg[0], env);
		if (str != NULL && isexecutable(str))
			exarg[0] = str;
		if (str != NULL && !(isexecutable(str)))
		{
			perror("access");
			continue;
		}
		session = fork();
		if (session == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (session == 0 && str = NULL)
			process_other(exarg, env);
		else if (session == 0 && ismore_than_onecommand(argv))
			process_multiple(exarg, env);
		else if (session == 0 && !(ismore_than_onecommand(argv)))
			execute_command(exarg, env)
		waitpid(session, &wstatus, 0);
	}
	free(ptr);
}

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
		if (!(withbin(argv[0])))
			argv[0] = strjn("/bin/", argv[0]);
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
 * iscommand - used to check whether the passed argument is a command
 * 	It uses enviroment variable PATH to check
 * @str: string command to check
 * @env: array pointers holding enviroment var
 * Return: complete path or NULL incase none
 */
char *iscommand(char *str, char *env[])
{
	char *sptr = NULL, *path, *patharr[20];
	int i = 0, j, len, diff;
	bool withpath = false;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	createargv(0, patharr, path, "other", ':');
	while (patharr[i++] != NULL)
	{
		len = strlen(patharr[i]);
		diff = len;
		for (j = 0; j < len; j++)
		{
			if (str[j] != patharr[i][j] &&
					pathexist(strjn(patharr[i], str)))
			{
				sptr = strjn(patharr[i], str);
				withpath = true;
				break;
			}
			if (str[j] == patharr[i][j])
				diff--;
		}
		if (withpath || diff == 0;)
		{
			withpath = true
			break;
		}
	}
	return (sptr);
}

void execute_command(char *argv[], char *env[])
{
	execve(argv[0], argv, env);
	perror("execve");
}
