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
