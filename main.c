#include "main.h"

/**
 * main - progaram entry point
 * @argc: argv counter
 * @argv: arguments pased to the program
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	int ret;
	command com, *cmd = &com;

	print('e', __FILE__, __func__);
	initialize(argc, argv, env, &cmd);
	if (argc == 1)
	{
		interactive(cmd);
		return (EXIT_SUCCESS);
	}
	printf("argc = %d\n", argc);
	printarr(cmd->argv1, "argv1");
	printf("argv1[0] = %s\n", cmd->argv1[0]);
	if (isreadable(cmd->argv1[0]) && !(iscommand(&cmd->argv1[0], cmd)))
	{
		process_file(cmd->argv1[0], cmd);
		return (EXIT_SUCCESS);
	}
	if (ismultiple_command(cmd->argv1))
		ret = process_multiple(cmd->argv1, cmd);
	else if (iscommand(&cmd->argv1[0], cmd))
	{
		ret = execute_command(cmd->argv1, cmd);
		if (ret == -1)
			is_exit(errno, cmd);
	}
	else
	{
		ret = execute_custom(cmd->argv1, cmd);
		if (ret == -1)
			is_exit(errno, cmd);
	}
	free_onexit(cmd);
	print('s', __FILE__, __func__);
	return (ret);
}

/**
 * initializer - initializes program variables
 * @argc: argv counter
 * @argv: arguments passed to the program
 */
void initialize(int argc, char *argv[], char *env[],command **cmd)
{
	int i;

	print('e', __FILE__, __func__);
	(*cmd)->p_name = argv[0];
	(*cmd)->argc = argc;
	(*cmd)->env = malloc(ARR_SIZE * sizeof(char *));
	(*cmd)->argv1 = malloc(ARR_SIZE * sizeof(char *));
	(*cmd)->argv2 = malloc(50 * sizeof(char *));
	if (((*cmd)->env == NULL) || ((*cmd)->argv1 == NULL) ||
			((*cmd)->argv2 == NULL))
	{
		perror((*cmd)->p_name);
		is_exit(errno, *cmd);
	}
	for (i = 0; i < ARR_SIZE; i++)
	{
		(*cmd)->argv1[i] = NULL;
		(*cmd)->env[i] = NULL;
	}
	for (i = 0; argv[i] != NULL; i++)
		(*cmd)->argv1[i] = argv[i + 1];
	(*cmd)->argv1[i] = NULL;

	for (i = 0; env[i] != NULL; i++)
		(*cmd)->env[i] = env[i];
	(*cmd)->env[i] = NULL;

	if (argc == 1)
		(*cmd)->fd = stdin;
	printarr((*cmd)->argv1, "argv1");
	print('l', __FILE__, __func__);
}

/**
 * interactive - run session on interactive shell
 */
void interactive(command *cmd)
{
	char *ptr = NULL, *prompt = "$ ";
	ssize_t ret;
	size_t count = 0;

	print('e', __FILE__, __func__);
	while (true)
	{
		/*signal(SIGINT, sig_handler);*/
		write(-1, prompt, 2);
		ret = getline(&ptr, &count, cmd->fd);
		if (ret == -1)
			is_exit(errno, cmd);
		stripstr(&ptr);
		if (ptr == NULL)
			continue;
		createargv(cmd->argv1, ptr, 32, cmd);
		if(ismultiple_command(cmd->argv1))
			process_multiple(cmd->argv1, cmd);
		else if (isreadable(cmd->argv1[0]) &&
					!(iscommand(&cmd->argv1[0], cmd)))
			process_file(cmd->argv1[0], cmd);
		else if (iscommand(&cmd->argv1[0], cmd))
		{
			printf("str: %s\n", cmd->argv1[0]);
			execute_command(cmd->argv1, cmd);
		}
		else
			execute_custom(cmd->argv1, cmd);
		free_half(cmd);
	}
	print('r', __FILE__, __func__);
}

/**
 * sig_handler - handles sinal interupts
 * @signum: signal interupt value
 */
void sig_handler(int __attribute__((unused)) signum)
{
	/*is_exit(0);*/
}
