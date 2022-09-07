#include "main.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "", *str;
	extern char *environ[];

	inicialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (argc == 1)
	{/* enter interactive mode */
		prompt = PROMPT_MSG;
		sisifo(prompt, data);
	}
	else
	{
		for (i = 0; i < argc; i++)
			argv[i] = argv[i + 1];
		argv[argc] = NULL;
		str = iscommand(argv[0], getenv("PATH"));
		if (str != NULL && access(str, X_OK) == -1)
		{
			perror(data->program-name);
			return (errno);
		}
		if (str != NULL && access(str, X_OK) == 0)
		{
			argv[0] = str;
			execve(argv[0], argv, environ);
			perror(data->program_name);
			return (errno);
		}
		if (str = NULL && access(argv[0], R_OK) == 0)
		{
			data->file_descriptor = open(argv[0], O_RDONLY);
			if (data->file_descriptor == -1)
			{
				perror(data->program_name);
				return (errno);
			}
			prompt = "";
			sisinfo(prompt, data);
		}
		else
		{
			perror(data->program_name);
			return (errno);
		}
	}	
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * inicialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void inicialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * sisifo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void sisifo(char *prompt, data_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
