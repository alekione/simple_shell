#include "main.h"

int checkfile(char *filepath)
{
	struct stat sb;

	return (lstat(filepath, &sb));
}
