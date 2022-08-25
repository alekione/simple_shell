#include "main.h"

/**
 * checkfile - looks whether a file exists on the given path
 * @filepath: given path to file
 * If it exists,
 * Return: 0 or -1 if it doesn't
 */
int checkfile(char *filepath)
{
	struct stat sb;

	return (lstat(filepath, &sb));
}

/**
 * withbin - checks whether the passed text starts with /bin/
 * @str: string from the user
 * Return: 0 if true, -1 if false
 */
int withbin(char *str)
{
	char *ptr = "/bin/";
	int i;

	for (i = 0; i < 5; i++)
	{
		if (str[i] != ptr[i])
			return (-1);
	}
	return (0);
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
	char chr, *ex = "exit";

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
	if (strcmp(str, ex) == 0)
		exit(EXIT_SUCCESS);
	return (str);
}
