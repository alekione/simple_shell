#include "main.h"

/**
 * cd - change current working dir
 * @dir: character pointer holding the new directory argument
 * Return: -1 on error 0 on success
 */
int cd(char *argv[], command *cmd)
{
	char *cwd, *hme = "-", *dir = argv[1];
	int cdir;

	print('e', __FILE__, __func__);
	if (_strcmp(dir, hme) == 0)
		dir = _getenv("HOME", cmd);
	if (access(dir, F_OK | X_OK) == -1)
	{
		perror(cmd->p_name);
		return (EXIT_FAILURE);
	}
	cwd = _getenv("PWD", cmd);
	set_env("PWD", dir, cmd);
	cdir = chdir(dir);
	if (cdir == -1)
	{
		perror(cmd->p_name);
		set_env("PWD", cwd, cmd);
		return (EXIT_FAILURE);
	}
	printf("%s - return success\n", __func__);
	print('r', __FILE__, __func__);
	return (EXIT_SUCCESS);
}
