#include "main.h"

/**
 * process_dollar_sign - checks whether there's a var subtitute on the a str
 * @argv: array of command pointers
 */
void process_dollar_sign(char *argv[])
{
	int i, j = 0, len;

	while (argv[j] != NULL)
	{
		len = strlen(argv[j]);
		for (i = 0; i < len; i++)
		{
			if (argv[j][i] == '$' && argv[j][i + 1] != '\0')
			{
				 argv[j] = string_dollar(&argv[j]);
				break;
			}
		}
		j++;
	}
}

/**
 * string_dollar - converts variable substitiute variable
 * @str: string containing the dillar sign
 * Return: a processed string
 */
char* string_dollar(char **ptr)
{
	char *str = *ptr, *chr, sptr[1024];
	int i, j, len, ind = 0, counter = 0;

	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '$')
		{
			j = string_dollar2(i, len, str, &chr);
			if (counter == 1)
			{
				sptr[ind] = '\0';
				_strcpy(&sptr, chr);
				ind += (int)strlen(chr);
			}
			i += j;
		}
		else
		{
			sptr[ind] = str[i];
			counter = 1;
			ind++;
		}
		if (counter == 0 && i >= len -1)
		{
			return (chr);
		}
	}
	*ptr = strdup(sptr);
	return (*ptr);
}

/**
 * string_dollar2 - continues string_dollar function
 * @i: index position
 * @len: string len
 * @str: string for comparison
 * @chr: pointer to hold results
 * Return: new index position
 */
int string_dollar2(int i, int len, char *str, char **chr)
{
	int j, ind;
	char sptr[20];

	j = 1;
	if (str[i + 1] == '?')
		*chr = getenv("EXT_VAL");
	else if (str[i + 1] == '$')
		*chr = num_tostring(getppid());
	else
	{
		ind = 0;
		for (j = i + 1; j < len; j++)
		{
			if (str[j] != '$')
	 			sptr[ind] = str[j];
			if (str[j] == '$')
				break;
			ind++;
		}
		sptr[ind] = '\0';
		*chr = getenv(sptr);
	}
	return (j);
}

/**
 * num_string - converts a number to  a string
 * @num: number to convert
 * Return: string number
 */
char *num_tostring(long unsigned int num)
{
	char *sptr, ptr[20], str[20];
	int i, ind = 0, m = 0;

	while (num != 0)
	{
		ptr[ind] = (num % 10) + '0';
		num /= 10;
		ind++;
	}
	ptr[ind] = '\0';
	for (i = ind; i > 0; i--)
	{
		str[m] = ptr[i - 1];
		m++;
	}
	str[m] = '\0';
	sptr = strdup(str);
	return (sptr);
}

/**
 * converts a character into a string
 * @c: char to convert
 * Return: string character
 */
void _strcpy(char (*str1)[], char *str2)
{
	int i = 0, j = 0;

	while (*(*str1 + i) != '\0')
		i++;
	while (str2[j] != '\0')
	{
		*(*str1 + i) = str2[j];
		i++;
		j++;
	}
	*(*str1 + i) = '\0';
}
