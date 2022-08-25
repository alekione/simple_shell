#include "main.h"

/**
 * strjn - join two pointer strings from the main
 * Works like strcat function
 * @str1: first string
 * @str2: second string
 * Return: a joined string
 */
char *strjn(char *str1, char *str2)
{
	char *str = (char *)malloc(20 * sizeof(char));
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i;

	if (str2 == NULL)
		return (NULL);
	for (i = 0; i < len1; i++)
		str[i] = str1[i];
	for (i = 0; i < len2; i++)
		str[i + len1] = str2[i];
	str[len1 + len2] = '\0';
	return (str);
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
	char *str;
	/**
	 *  if there is only one argument passed,
	 * the program should enter into interactive mode
	 * else, get argument number and determine the method to use
	 */
	if (argc == 1)
		interactive(env);
	str = argv[1];
	createargv(argc, argv, NULL, "main");
	if (checkfile(argv[0]) == -1)
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
		 * stripstr() is used to do this, and also to exit interactive
		 * mode, if stripped string is "exit"
		 */
		createargv(0, exarg, stripstr(ptr), "interactive");
		str = exarg[0];
		if (withbin(exarg[0]) == -1 && exarg[0] != NULL)
			exarg[0] = strjn("/bin/", exarg[0]);
		if (checkfile(exarg[0]) == -1)
		{
			perror(str);
			continue;
		}
		session = fork();
		if (session == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (session == 0)
		{
			execve(exarg[0], exarg, env);
			perror("execve");
			_exit(session);
		}
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
 *	the main() and interactive() methods.
 *	It manupulates the pointers to pointer arrays.
 */
void createargv(int argc, char *argv[], char *str, char source[])
{
	char *word_ptr,  word[50], main[] = "main",
		interactive[] = "interactive", chr;
	int i = 0, count = 0, ind = 0, len;

	if (strcmp(source, main) == 0)
	{
		if (withbin(argv[1]) == -1)
			argv[1] = strjn("/bin/", argv[1]);
		for (i = 1; i < argc; i++)
			*(argv + (i - 1)) = argv[i];
		*(argv + (argc - 1)) = NULL;
	}
	if (strcmp(source, interactive) == 0)
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
			if ((chr == ' ' || chr == '\0') && ind > 0)
			{
				word[ind] = '\0';
				word_ptr = strdup(word);
				*(argv + count) = word_ptr;
				ind = 0;
				count++;
			}
			if (chr != ' ')
			{
				word[ind] = chr;
				ind++;
			}
			i++;
		}
		*(argv + count) = NULL;
	}
}
