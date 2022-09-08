#include "main.h"

/**
 * iscommand - used to check whether the passed argument is a command
 * It uses enviroment variable PATH to check
 * @ptr: string command to check
 * @path: pointers holding enviroment value path
 * Return: complete path or NULL incase none
 */
void iscommand(char **ptr, char *path)
{
	char *chr1, *patharr[20], *str = *ptr;
	int i = 0, j, len, diff;

	if (path == NULL || str == NULL)
	{
		*ptr = NULL;
		return;
	}
	createargv(patharr, path, ':');
	while (patharr[i] != NULL)
	{
		len = strlen(patharr[i]);
		diff = len;
		for (j = 0; j < len; j++)
		{
			if (str[j] == patharr[i][j])
			{
				diff--;
				continue;
			}
			chr1 = str_concat(patharr[i], "/");
			chr1 = str_concat(chr1, str);
			if (access(chr1, X_OK) == 0)
				break;
			chr1 = NULL;
			break;
		}
		if (diff == 0)
			chr1 = str;
		if (chr1 != NULL || diff == 0)
			break;
		i++;
	}
	str = NULL;
	*ptr = chr1;
}

/**
 * createargv - is used to create character pointer array, for execve() method
 *	that is used to run commands.
 *	Since in main, the number of arguments passed is already given, so
 *	we pass it as argc in this function.
 *	On interactive shell the number of passed args is not determined unless
 *	it's calculated manually here.
 * @argv: arguments passed to the function, from the main and a NULL
 *	pointer from interactive shell
 * @str: string holding the passed arguments, the main function passes NULL
 *	while interactive shell passes argument from the user
 * @delim: delimeter to use for separating string
 *	It manupulates the pointers to pointer arrays.
 */
void createargv(char *argv[], char *str, char delim)
{
	char word[50], chr;
	int i = 0, count = 0, ind = 0, len;

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
			*(argv + count) = strdup(word);
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
}
