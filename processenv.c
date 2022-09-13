#include "main.h"

/**
 * set_env - sets an enviromental variable
 * @name - name of the variable
 * @val: value of the variable
 * Return: 0 on success
 */
int set_env(char *name, char *val, command *cmd)
{
	char *str, *chr1;
	int i;

	free_argv(cmd->argv2);
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		createargv(cmd->argv2, cmd->env[i], '=', cmd);
		if (_strcmp(cmd->argv2[0], name) == 0)
			break;
		free_argv(cmd->argv2);
	}
	if (cmd->env[i] == NULL)
	{
		strjn(&name, "=");
		chr1 = name;
		strjn(&chr1, val);
		free_str(&name);
		cmd->env[i] = chr1;
		cmd->env[i + 1] = NULL;
	}
	else
	{
		str = cmd->argv2[i];
		strjn(&str, "=");
		chr1 = str;
		strjn(&chr1, val);
		free_str(&str);
		cmd->env[i] = chr1;
	}
	errno = 0;
	free_argv(cmd->argv2);
	return (EXIT_SUCCESS);
}

/**
 * _getenv - searches for an enviroment variable
 * @name: name of the variable
 * Return: str pointer to the value
 */
char *_getenv(char *name, command *cmd)
{
	int i = 0, ind = 0, j;
	char *str = malloc(ARR_SIZE * sizeof(char));
	bool isenv = false;

	for (; cmd->env[i] != NULL; i++)
	{
		if (cmd->env[i][0] != name[0])
			continue;
		ind = 0;
		for (j = 0; j < _strlen(cmd->env[i]); j++)
		{
			if (cmd->env[i][j] == '=')
			{
				if (j != _strlen(name))
					break;
				str[ind] = '\0';
				if (_strcmp(str, name) == 0)
				{
					isenv = true;
					break;
				}
				break;
			}
			str[ind] = cmd->env[i][j];
			ind++;
		}
		if (isenv)
			break;
/*		free_str(&str);*/
	}
	free_str(&str);
	errno = 0;
	if (cmd->env[i] == NULL)
		return (NULL);
	free_argv(cmd->argv2);
	createargv(cmd->argv2, cmd->env[i], '=', cmd);
	return (cmd->argv2[1]);
}

/**
 * unset_env - removes enviroment variable
 * @name: name of the variable
 * Return: 0 on success
 */
int unset_env(char *name, command *cmd)
{
	int i;

	free_argv(cmd->argv2);
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		createargv(cmd->argv2, cmd->env[i], '=', cmd);
		if (_strcmp(cmd->argv2[0], name) == 0)
			break;
		free_argv(cmd->argv2);
	}
	free_argv(cmd->argv2);
	errno = 0;
	if (cmd->env[i] == NULL)
		return (EXIT_FAILURE);
	while(cmd->env[i] != NULL)
	{
		cmd->env[i] = cmd->env[i + 1];
		i++;
	}
	return (EXIT_SUCCESS);
}
