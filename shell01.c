#include "main.h"

/**
 * ismultiple_command - checks whether the passed argument has
 * more than one command
 * @argv: array pointers holding commands
 * Return: true or false
 */
bool ismultiple_command(char *argv[])
{
	char *str[] = {"||", "&&", ";"};
	int m = 0, j;

	while (m < 3)
	{
		j = 0;
		while (argv[j] != NULL)
		{
			if (_strcmp(argv[j], str[m]) == 0)
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
 */
bool iscommand(char **str, command *cmd)
{
	char *env, *chr1, *chr2;
	int i, j, len, diff = 0;

	env = _getenv("PATH", cmd);
	createargv(cmd->argv2, env, ':', cmd);
	for (i = 0; cmd->argv2[i] != NULL; i++)
	{
		len = _strlen(cmd->argv2[i]);
		diff = len;
		for (j = 0; j < len; j++)
		{
			if (*str[j] == cmd->argv2[i][j])
			{
				diff--;
				continue;
			}
			chr2 = cmd->argv2[i];
			strjn(&chr2, "/");
			chr1 = chr2;
			strjn(&chr1, *str);
			free_str(&chr2);
			if (isexecutable(chr1))
				break;
			free_str(&chr1);
			break;
		}
		if (diff == 0)
			break;
		if (chr1 != NULL)
		{
			errno = 0;
		/*	free_str(str);*/
			*str = chr1;
			break;
		}
	}
	free_argv(cmd->argv2);
	if (diff == 0 || chr1 != NULL)
		return (true);
	return (false);
}

/**
 * _strcmp - compares two string for similarity
 * @str1: string 1
 * @string2: string 2
 * Return: 0 if true or -1
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	if (_strlen(str1) != _strlen(str2))
		return (-1);
	for (i = 0; i < _strlen(str1); i++)
	{
		if (str1[i] != str2[i])
			return (-1);
	}
	return (0);
}
