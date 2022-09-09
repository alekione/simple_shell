#include "main.h"

/**
 * set_env - sets an enviromental variable
 * @name - name of the variable
 * @val: value of the variable
 * Return: 0 on success
 */
int set_env(char *name, char *val, command *cmd)
{
	char *str, *envarr[ARR_SIZE];
	int i;

	for (i = 0; cmd->env[i] != NULL; i++)
	{
		createargv(envarr, cmd->env[i], '=', cmd);
		if (_strcmp(envarr[0], name) == 0)
			break;
	}
	if (cmd->env[i] == NULL)
	{
		strjn(&name, "=", cmd);
		strjn(&name, val, cmd);
		cmd->env[i] = name;
		cmd->env[i + 1] = NULL;
	}
	else
	{
		str = envarr[i];
		strjn(&str, "=", cmd);
		strjn(&str, val, cmd);
		cmd->env[i] = str;
	}
	errno = 0;
	return (EXIT_SUCCESS);
}

/**
 * _getenv - searches for an enviroment variable
 * @name: name of the variable
 * Return: str pointer to the value
 */
char *_getenv(char *name, command *cmd)
{
	int i = 0, ind = 0, j, len, len1 = _strlen(name);
	char *str = malloc(ARR_SIZE * sizeof(char)), *argv[3];
	bool isenv = false;

	for (; cmd->env[i] != NULL; i++)
	{
		len = strlen(cmd->env[i]);
		ind = 0;
		for (j = 0; j < len; j++)
		{
			if (cmd->env[i][j] == '=')
			{
				if (j != len1)
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
	}
	free(str);
	createargv(argv, cmd->env[i], '=', cmd);
	errno = 0;
	if (cmd->env[i] == NULL)
		return (NULL);
	return (argv[1]);
}

/**
 * unset_env - removes enviroment variable
 * @name: name of the variable
 * Return: 0 on success
 */
int unset_env(char *name, command *cmd)
{
	int i;
	char *envarr[ARR_SIZE];

	for (i = 0; cmd->env[i] != NULL; i++)
	{
		createargv(envarr, cmd->env[i], '=', cmd);
		if (_strcmp(envarr[0], name) == 0)
			break;
	}
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
