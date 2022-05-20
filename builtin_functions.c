#include "sh.h"

/**
 * cdir_b - Changes the current working directory to the parameter
 * passed to cd.
 * if no parameter is passed it will change directory to HOME.
 * @line: A string representing the input from the user.
 */
void cdir_b(char *line)
{
	int index;
	int token_number;
	char **p_array;
	const char *delimiter = "\n ";

	token_number = 0;
	p_array = token_connector(line, delimiter, token_number);
	if (p_array[0] == NULL)
	{
		single_free(2, p_array, line);
		return;
	}
	if (p_array[1] == NULL)
	{
		index = find_path("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(p_array[1], "-") == 0)
		print_str(p_array[1], 0);

	else
		chdir(p_array[1]);
	double_free(p_array);
}

/**
 * environ_b - Prints all the environmental variables in the current shell.
 * @line: A string representing the input from the user.
 */
void environ_b(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * exit_b - Exits the shell. After freeing allocated resources.
 * @line: A string representing the input from the user.
 */
void exit_b(char *line)
{
	free(line);
	print_str("\n", 1);
	exit(1);
}

/**
 * check_built_ins - Finds the right function needed for execution.
 * @str: The name of the function that is needed.
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *str))(char *str)
{
	int i;

	builtin_t buildin[] = {
		{"exit", exit_b},
		{"env", environ_b},
		{"cd", cdir_b},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].f);
		}
	}
	return (NULL);
}

/**
 * built_in - Checks for builtin functions.
 * @command: An array of all the arguments passed to the shell.
 * @line: A string representing the input from the user.
 * Return: If function is found 0. Otherwise -1.
 */
int built_in(char **command, char *line)
{
	void (*build)(char *);

	build = check_built_ins(command[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", command[0]) == 0)
		double_free(command);
	build(line);
	return (0);
}
