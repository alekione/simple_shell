#include "main.h"

/**
 * isreadable - checks for read permissions on a given path
 * @path: path to check
 * Return: true or false
 */
bool isreadable(char *path)
{
	print('e', __FILE__, __func__);
	if (access(path, F_OK | R_OK) == 0)
	{
		printf("%s returning true\n", __func__);
		print('e', __FILE__, __func__);
		return (true);
	}
	printf("%s returning false\n", __func__);
	print('r', __FILE__, __func__);
	return (false);
}

/**
 * iswritable - checks for write permissions on given path
 * @path: path to check
 * Return: true or false
 */
bool iswritable(char *path)
{
	print('e', __FILE__, __func__);
	if (access(path, F_OK | W_OK) == 0)
	{
		printf("%s returning true\n", __func__);
		print('r', __FILE__, __func__);
		return (true);
	}
	printf("%s returning false\n", __func__);
	print('r', __FILE__, __func__);
	return (false);
}

/**
 * isexecutable - checks whether the given dir/file is executable
 * @path: path given
 * Return: true or false
 */
bool isexecutable(char *path)
{
	print('e', __FILE__, __func__);
	if (access(path, F_OK | X_OK) == 0)
	{
		printf("%s returning true\n", __func__);
		print('r', __FILE__, __func__);
		return (true);
	}
	printf("%s returning false\n", __func__);
	print('r', __FILE__, __func__);
	return (false);
}
