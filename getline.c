#include "main.h"

#if !(defined _POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200809L

#ifndef SSIZE_MAX
#define SSIZE_MAX (SIZE_MAX >> 1)
#endif
#define INITALLOC  16
#define ALLOCSTEP  16
ssize_t getline2(char **pline_buf, size_t *pn, FILE *fin);

/**
 * getline- reads a line from a given file descriptor
 * @pline_buf: line buffer
 * @pn: buffer size
 * @fin: file descriptor
 * Return: size of characters read
 */
ssize_t getline(char **pline_buf, size_t *pn, FILE *fin)
{
	if ((pline_buf == NULL) || (pn == NULL) || (fin == NULL))
	{
		errno = EINVAL;
		return (-1);
	}
	if (*pline_buf == NULL)
	{
		*pline_buf = malloc(INITALLOC);
		if (*pline_buf == NULL)
		{
			return (-1);
		}
		else
		{
			*pn = INITALLOC;
		}
	}
	return (_getline2(pline_buf, pn, fin));
}

/**
 * getline2 - continues getline function
 * @pline_buf: line buffer
 * @pn: size of buffer
 * @fin: file descriptor
 * Return: characters read
 */
ssize_t getline2(char **pline_buf, size_t *pn, FILE *fin)
{
	size_t num_read = 0, n_realloc;
	int c;
	char *tmp;
	{
		while ((c = getc(fin)) != EOF)
		{
			num_read++;
			if (num_read >= *pn)
			{
				n_realloc = *pn + ALLOCSTEP;
				tmp = realloc(*pline_buf, n_realloc + 1);
				if (tmp != NULL)
				{
					*pline_buf = tmp;
					*pn = n_realloc;
				}
				else
				{
					return (-1);
				}
				if (*pn > SSIZE_MAX)
				{
					errno = ERANGE;
					return (-1);
				}
			}
			(*pline_buf)[num_read - 1] = (char) c;
			if (c == '\n')
			{
				break;
			}
		}
		if (c == EOF)
		{
			errno = 0;
			return (-1);
		}
	}
	(*pline_buf)[num_read] = '\0';
	return ((ssize_t) num_read);
}
#endif
