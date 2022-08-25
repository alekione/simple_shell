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
		char __attribute__((unused)) *env[])
{
	char *exarg[] = {NULL, NULL, NULL,NULL}, *exenv[] = {NULL};

	/* if there is only one argument passed,
	 * the program should enter into interactive mode
	 * else, get argument number and determine the method to use
	 */
	if (argc == 1)
	{
		interactive();
	}
	if (argc == 2)
	{
		exarg[0] = argv[1];
		if (withbin(argv[1]) == -1)
			exarg[0] = strjn("/bin/", argv[1]);
		execve(exarg[0], exarg, exenv);
		perror("execve");
	}
	return (0);
}

/**
 * interactive - the interactive section is controlled by this function.
 * Works like a shell inside a shell i.e.,
 * it creates its own prompt and execute commands passed into it
 * It does not return anything
 */
void interactive(void)
{
	char *ptr = NULL, prompt[] = " ($)";
	char *exarg[] = {NULL, NULL, NULL, NULL}, *exenv[] = {NULL};
	pid_t session;
	size_t size = 0;

	while (true)
	{
		write(1, &prompt, 4);
		getline(&ptr, &size, stdin);
		/**
		 * i found that getline method, is adding another char at the end
		 * the char is causing the program to crash so,
		 * so it has to be stripped before continuing with the program.
		 * stripstr() is used to do this
		 */
		exarg[0] = stripstr(ptr);
		if (withbin(ptr) == -1)
			exarg[0] = strjn("/bin/", exarg[0]);
		session = fork();
		if (session == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (session == 0)
		{
			execve(exarg[0], exarg, exenv);
			perror("execve");
			sleep(1);
			_exit(session);
		}
		sleep(1);
	}
	free(ptr);

}
