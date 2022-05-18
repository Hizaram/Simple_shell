#include "sh.h"

/**
 * parser - Takes the command line and checks to see if there are arguments.
 * This fucntion also handles freeing memory that is no longer needed.
 * @line: A pointer to a string. It is always NULL
 * when the function is initialised.
 * @size: A holder for numbers of size_t. Will always be initialized to 0.
 * @command_counter: A counter that holds the number of commands
 * that have been fed into the shell.
 * @av: Program name of the shell.
 */

void parser(char *line, size_t size, int command_counter, char **av)
{
	int i;
	ssize_t read_len;
	int token_number;
	char **p_array;
	const char *delimiter = "\n\t ";

	token_number = 0;
	if (isatty(0))
		write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	signal(SIGINT, sigintH);
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		if (read_len == EOF)
			exit(0);
		p_array = token_connector(line, delimiter, token_number);
		if (p_array[0] == NULL)
		{
			single_free(2, p_array, line);
			return;
		}
		i = built_in(p_array, line);
		if (i == -1)
			create_child(p_array, line, command_counter, av);
		for (i = 0; p_array[i] != NULL; i++)
			free(p_array[i]);
		single_free(2, p_array, line);
	}
	else
		exit_b(line);
}

/**
 * create_child - Creates a child process that executes another program.
 * @p_array: An array of pointers to strings containing the possible name
 * of a program and its parameters. This array is NULL terminated.
 * @line: The contents of the read line.
 * @count: A counter keeping track of how many commands have been entered
 * into the shell.
 * @av: Name of the program running the shell
 */

void create_child(char **p_array, char *line, int count, char **av)
{
	pid_t id;
	int status;
	int i;
	int check;
	struct stat buf;
	char *tmp_command;
	char *command;

	id = fork();
	if (id == 0)
	{
		tmp_command = p_array[0];
		command = path_finder(p_array[0]);
		if (command == NULL)
		{
			/*Looking for file in current directory*/
			check = stat(tmp_command, &buf);
			if (check == -1)
			{
				error_printing(av[0], count, tmp_command);
				print_str(": not found", 0);
				single_free(2, line, tmp_command);
				for (i = 1; p_array[i]; i++)
					free(p_array[i]);
				free(p_array);
				exit(100);
			}
			/*file exist in cwd or has full path*/
			command = tmp_command;
		}
		p_array[0] = command;
		if (p_array[0] != NULL)
		{
			if (execve(p_array[0], p_array, environ) == -1)
				exec_error(av[0], count, tmp_command);
		}
	}
	else
		wait(&status);
}

/**
 * token_connector - Allows the accesibility of token functions
 * with other parts of the program.
 * @line: A string containing the raw user input.
 * @delimiter: A constant string containing the symbols
 * that will be used to split
 * the inputed strings into tokens.
 * @token_number: Holds the amount  of tokens in a string.
 * Return: Upon success an array of tokens representing the command. Otherwise
 * returns NULL.
 */

char **token_connector(char *line, const char *delimiter, int token_number)
{
	char **p_array;

	token_number = count_token(line, delimiter);
	if (token_number == -1)
	{
		free(line);
		return (NULL);
	}
	p_array = tokenize(token_number, line, delimiter);
	if (p_array == NULL)
	{
		free(line);
		return (NULL);
	}

	return (p_array);
}

/**
 * tokenize - Separates the string into an array of tokens
 * splitted using the delimiter.
 * DON'T FORGET TO FREE
 * on receiving function when using tokenize.
 * @token_number: An integer representing the amount of tokens in the array.
 * @line: String that is separated by an specified delimeter
 * @delimiter: The desired delimiter to separate tokens.
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL.
 */

char **tokenize(int token_number, char *line, const char *delimiter)
{
	int i;
	char **buffer;
	char *token;
	char *line_cp;

	line_cp = _strdup(line);
	buffer = malloc(sizeof(char *) * (token_number + 1));
	if (buffer == NULL)
		return (NULL);
	token = strtok(line_cp, delimiter);
	for (i = 0; token != NULL; i++)
	{
		buffer[i] = _strdup(token);
		token = strtok(NULL, delimiter);
	}
	buffer[i] = NULL;
	free(line_cp);
	return (buffer);
}

/**
 * count_token - Counts tokens in the passed string.
 * @line: String that is separated by a specified delimeter
 * @delimiter: The desired delimeter to separate tokens.
 * Return: Upon success the total count of the tokens. Otherwise -1.
 */

int count_token(char *line, const char *delimiter)
{
	char *str;
	char *token;
	int i;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delimiter);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delimiter);
	free(str);
	return (i);
}
