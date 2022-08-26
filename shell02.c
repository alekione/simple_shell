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

	if (lstat(filepath, &sb) == -1)
		return (false);
	return (true);
}

/**
 * withbin - checks whether the passed text starts with /bin/
 * @str: string from the user
 * Return: 0 if true, -1 if false
 */
bool withbin(char *str)
{
	char *ptr = "/bin/";
	int i;

	for (i = 0; i < 5; i++)
	{
		if (str[i] != ptr[i])
			return (false);
	}
	return (true);
}

/**
 * stripstr - used to strip newline && space char(s) at the end
 * since it is used to strip a string from cmd line, it is also used
 * to exit the program.
 * @str: string to strip
 * Return: a stripped string
 */
char *stripstr(char *str)
{
	int i = 2, len = strlen(str);
	char chr;

	if (len == 1)
		return (NULL);
	*(str + len - 1) = '\0';
	while (true)
	{
		chr = *(str + len - i);
		if (chr != ' ')
			break;
		*(str + len - i) = '\0';
		i++;
	}
	return (str);
}

/**
 * strjn - join two pointer strings from the main
 * Works like strcat function
 * @str1: first string
 * @str2: second string
 * Return: a joined string
 */
char *strjn(char *str1, char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	char *str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
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
 * more_than_one_command - checks whether the passed argument has 
 * 	more than one command
 * @argv: array pointers holding commands
 * Return: true or false
 */
bool ismore_than_onecommand(char *argv[])
{
	char *str[] = {"||", "&&", ';'};
	int i, j = 0;

	for (i = 0; i < 4; i++)
	{
		while (argv[j++] != NULL)
		{
			if (strcmp(argv[j], str[i]) == 0)
				return (true)
		}
	}
	return (false);
}
