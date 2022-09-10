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

	print('e', __FILE__, __func__);
	while (m < 3)
	{
		j = 0;
		while (argv[j] != NULL)
		{
			if (strcmp(argv[j], str[m]) == 0)
			{
				printf("%s returning true\n", __func__);
				print('r', __FILE__, __func__);
				return (true);
			}
			j++;
		}
		m++;
	}
	printf("%s returning false\n", __func__);
	print('r', __FILE__, __func__);
	return (false);
}

/**
 * iscommand - used to check whether the passed argument is a command
 * It uses enviroment variable PATH to check
 * @ptr: string command to check
 */
bool iscommand(char **str, command *cmd)
{
	char *env, *chr1, *chr2, *patharr[ARR_SIZE];
	int i, j, len, diff = 0;

	print('e', __FILE__, __func__);
	env = _getenv("PATH", cmd);
	createargv(patharr, env, ':', cmd);
	for (i = 0; patharr[i] != NULL; i++)
	{
		len = _strlen(patharr[i]);
		diff = len;
		for (j = 0; j < len; j++)
		{
			if (*str[j] == patharr[i][j])
			{
				diff--;
				continue;
			}
			chr2 = patharr[i];
			strjn(&chr2, "/");
			chr1 = chr2;
			strjn(&chr1, *str);
			free(chr2);
			if (isexecutable(chr1))
				break;
			free(chr1);
			chr1 = NULL;
			break;
		}
		if (diff == 0)
			break;
		if (chr1 != NULL)
		{
			errno = 0;
			free(*str);
			*str = chr1;
			printf("str: %s\n", *str);
			break;
		}
	}
	printf("returning %s\n", chr1);
	printf("%s returning true\n", __func__);
	print('r', __FILE__, __func__);
	if (diff == 0 || chr1 != NULL)
		return (true);
	printf("%s returning false\n", __func__);
	return (false);
}

/**
 * add_to_history - add a pointer to th history
 * @str: pointer to memory location
 * \
void add_to_hist(char **str, command *cmd)
{
	char **list2;
	int i;

	print('e', __FILE__, __func__);
	if (cmd->hist_count == cmd->max_count - 1)
	{
		cmd->max_count += ARR_SIZE;
		list2 = realloc(cmd->list, cmd->max_count * sizeof(char *));
		if (list2 == NULL)
		{
			perror(cmd->p_name);
			return;
		}
		for (i = cmd->hist_count; i < cmd->max_count; i++)
			list2[i] = NULL;
		cmd->list = list2;
	}
	cmd->list[cmd->hist_count] = *str;
	cmd->hist_count += 1;
	cmd->list[cmd->hist_count] = NULL;
	print('r', __FILE__, __func__);
}*/

/**
 * _strcmp - compares two string for similarity
 * @str1: string 1
 * @string2: string 2
 * Return: 0 if true or -1
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	print('e', __FILE__, __func__);
	printf("str in: %s\nstr in: %s\n", str1, str2);
	if (_strlen(str1) != _strlen(str2))
		return (-1);
	for (i = 0; i < _strlen(str1); i++)
	{
		if (str1[i] != str2[i])
		{
			print('r', __FILE__, __func__);
			return (-1);
		}
	}
	print('r', __FILE__, __func__);
	return (0);
}
