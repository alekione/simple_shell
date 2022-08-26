#include "main.h"

/**
 * checkR - checks for read permissions on a given path
 * @path: path to check
 * Return: true or false
 */
bool isreadable(char *path)
{
	if (access(path, F_OK | R_OK) == 0)
		return (true);
	return (false);
}

/**
 * checkW - checks for write permissions on given path
 * @path: path to check
 * Return: true or false
 */
bool iswritable(char *path)
{
	if (access(path, F_OK | W_OK) == 0)
		return (true);
	return (false);
}

/**
 * checkX - checks whether the given dir/file is executable
 * @path: path given
 * Return: true or false
 */
bool isexecutable(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (true);
	return (false);
}
