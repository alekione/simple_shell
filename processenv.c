#include "main.h"

/**
 * processenv - used to set or unset enviroment variables
 * @arg: array of string pointers holding instructions
 * Return: 0 on success -1 on error
 */
int  processenv(char *argv[])
{
	char *set = "setenv", *unset = "unsetenv";
	int res = 0;

	if (strcmp(argv[0], set) == 0)
		res = setenv(argv[1], argv[2], 1);
	if (strcmp(argv[0], unset) == 0)
		res = unsetenv(argv[1]);
	if (res == -1)
		perror(argv[0]);
	return (res);
}
