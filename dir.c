#include "main.h"

/**
 * cd - change current working dir
 * @argv: array pointer holding instructions
 * Return: -1 on error 0 on success
 */
int cd(char *dir)
{
	char *cwd = (char *)malloc(100 * sizeof(char));
	char *hme = "-";
	int cdir;
	

	if (cwd == NULL)
	{
		perror(getenv("ERR_MSG"));
		return (EXIT_FAILURE);
	}
	if (strcmp(dir, hme) == 0)
		dir = getenv("HOME");
	if (!(pathexist(dir)))
	{
		perror(getenv("ERR_MSG"));
		free(cwd);
		return (EXIT_FAILURE);
	}
	getcwd(cwd, 100);
	setenv("PWD", dir, 1);
	cdir = chdir(dir);
	if (cdir == -1)
	{
		setenv("EXT_VAL", num_tostring(errno), 1);
		perror(getenv("ERR_MSG"));
		setenv("PWD", cwd, 1);
		free(cwd);
		return (EXIT_FAILURE);
	}
	free(cwd);
	setenv("EXT_VAL", "0", 1);
	return (EXIT_SUCCESS);
}
