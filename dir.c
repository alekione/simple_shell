#include "main.h"

/**
 * cd - change current working dir
 * @dir: character pointer holding the new directory argument
 * Return: -1 on error 0 on success
 */
int cd(char *dir)
{
	char *cwd = (char *)malloc(100 * sizeof(char));
	char *hme = "-";
	int cdir;

	if (cwd == NULL)
	{
		perror(p_name);
		return (EXIT_FAILURE);
	}
	if (strcmp(dir, hme) == 0)
		dir = getenv("HOME");
	if (!(pathexist(dir)))
	{
		perror(p_name);
		free(cwd);
		return (EXIT_FAILURE);
	}
	getcwd(cwd, 100);
	setenv("PWD", dir, 1);
	cdir = chdir(dir);
	if (cdir == -1)
	{
		perror(p_name);
		setenv("PWD", cwd, 1);
		free(cwd);
		return (EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}
