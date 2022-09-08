#include "main.h"

/**
 * pathexist - looks whether a file exists on the given path
 * @filepath: given path to file
 * If it exists,
 * Return: 0 or -1 if it doesn't
 */
bool pathexist(char *filepath)
{
	struct stat sb;

	if (lstat(filepath, &sb) == 0)
		return (true);
	return (false);
}

/**
 * stripstr - used to strip newline && space char(s) at the end
 * since it is used to strip a string from cmd line, it is also used
 * to exit the program.
 * @ptr: string to strip
 * Return: a stripped string
 */
void stripstr(char **ptr)
{
	char *str = strdup(*ptr), chr, end = EOF;
	int i = 2, len = strlen(str);

	if (*ptr[0] == end)
		exit(errno);
	if (len == 1)
	{
		*ptr = NULL;
		return;
	}
	*(str + len - 1) = '\0';
	while (true)
	{
		chr = *(str + len - i);
		if (chr != ' ')
			break;
		*(str + len - i) = '\0';
		i++;
	}
	free(*ptr);
	*ptr = str;
}

/**
 * strjn - join two pointer strings from the main
 * Works like strcat function
 * @str1: first string
 * @str2: second string
 */
void strjn(char **str1, char *str2)
{
	char *str, *ptr = strdup(*str1);
	int len1, len2 = strlen(str2);
	int i;

	if (str2 == NULL || len2 == 0)
		return;
	len1 = strlen(ptr);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	for (i = 0; i < len1; i++)
		str[i] = ptr[i];
	for (i = 0; i < len2; i++)
		str[i + len1] = str2[i];
	str[len1 + len2] = '\0';
	free(ptr);
	*str1 = str;
}

/**
 * ismore_than_onecommand - checks whether the passed argument has
 * more than one command
 * @argv: array pointers holding commands
 * Return: true or false
 */
bool ismore_than_onecommand(char *argv[])
{
	char *str[] = {"||", "&&", ";"};
	int m = 0, j;

	while (m < 3)
	{
		j = 0;
		while (argv[j] != NULL)
		{
			if (strcmp(argv[j], str[m]) == 0)
				return (true);
			j++;
		}
		m++;
	}
	return (false);
}

/**
 * iscommand - used to check whether the passed argument is a command
 * It uses enviroment variable PATH to check
 * @ptr: string command to check
 * @path: pointers holding enviroment value path
 * Return: complete path or NULL incase none
 */
void iscommand(char **ptr, char *path)
{
	char *chr1 = NULL, *chr2, *patharr[20], *str = *ptr;
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
			chr1 = patharr[i];
			strjn(&chr1, "/");
			chr2 = chr1;
			strjn(&chr1, str);
			free(chr2);
			if (isexecutable(chr1))
				break;
			free(chr1);
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
	_free(patharr, &str);
	*ptr = chr1;
}
