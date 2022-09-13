#include "main.h"

/**
 * createargv - used t separate words from a string
 * @argv: array of pointers to hold words
 * @str: string to split
 * @delim: delimeter used for spltting
 */
void createargv(char **argv, char *str, char delim, command *cmd)
{
	char word[ARR_SIZE], chr;
	int i = 0, count = 0, ind = 0, len;

	if (str == NULL)
	{
		argv[0] = NULL;
		return;
	}
	len = _strlen(str);
	for (i = 0; i <= len; i++)
	{
		chr = str[i];
		if ((chr == delim || chr == '\0' || chr == '#') && ind > 0)
		{
			word[ind] = '\0';
			argv[count] = _strdup(word, cmd);
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
	}
	argv[count] = NULL;
}

/**
 * _strdup - duplicates a given string
 * @str: string to duplicate
 * Return: a new string
 */
char *_strdup(char *str, command *cmd)
{
	int len, i;
	char *ptr;

	len = _strlen(str);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
	{
		perror(cmd->p_name);
		is_exit(errno, cmd);
	}
	for (i = 0; i < len; i++)
		ptr[i] = str[i];
	ptr[len] = '\0';
	return (ptr);
}

/**
 * _strlen - calculates length of a string
 * @str: string to count
 * Return: length of the string
 */
int _strlen(char *str)
{
	int len;

	if (str == NULL)
		return (-1);
	for (len = 0; str[len] != '\0'; len++)
		;
	return (len);
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
	char *str = *ptr;
	int i = 0, j, len = _strlen(*ptr);

	if (len == 1)
	{
		*ptr = NULL;
		return;
	}
	str[len - 1] = '\0';
	while (true)
	{
		if (i == len - 1)
			break;
		if (str[i] == ' ' && str[i - 1] == ' ')
		{
			for (j = i; j < len - 1; j++)
				str[j] = str[j + 1];
			len--;
		}
		i++;
	}
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
	char *str, *ptr = *str1;
	int len1, len2 = _strlen(str2);
	int i;

	if (str2 == NULL || len2 == 0)
		return;
	len1 = _strlen(ptr);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	for (i = 0; i < len1; i++)
		str[i] = ptr[i];
	for (i = 0; i < len2; i++)
		str[i + len1] = str2[i];
	str[len1 + len2] = '\0';
	*str1 = str;
}
