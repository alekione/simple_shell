#include "main.h"

/**
 * cd - change current working dir
 * @argv: array pointer holding instructions
 * Return: -1 on error 0 on success
 */
int cd(char *argv[])
{
	char *cwd = (char *)malloc(100 * sizeof(char));
	char *argv2[3], *ptr = "setenv", *dir = argv[1], *hme = "-";
	int env, cdir;
	
	if (cwd == NULL)
	{
		perror(argv[0]);
		return (-1);
	}
	if (strcmp(dir, hme) == 0)
		dir = getenv("HOME");
	if (!(pathexist(dir)))
	{
		perror(argv[0]);
		free(cwd);
		return (-1);
	}
	getcwd(cwd, 100);
	argv2[0] = ptr;
	argv2[1] = "PWD";
	argv2[2] = dir;
	env = processenv(argv2);
	if (env == -1)
	{
		free(cwd);
		return (env);
	}
	cdir = chdir(dir);
	if (cdir == -1)
	{
		perror(argv[0]);
		argv2[2] = cwd;
		processenv(argv2);
		free(cwd);
		return (-1);
	}
	free(cwd);
	return (0);
}
