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
 * used to strip newline char at the end
 * @str: string to strip
 * Return: a stripped string
 */
char *stripstr(char *str)
{
	int len = strlen(str);

	if (len == 1)
		return (NULL);
	*(str + len - 1) = '\0';
	return (str);
}
