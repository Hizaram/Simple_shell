#include "sh.h"

/**
 * main - Entry point of the program.
 * @ac: The number of parameters passed to the executable file. In the case
 * this variable will not be used.
 * @av: The name of the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int ac, char **av)
{
	char *line;
	size_t size;
	int command_count;

	command_count = 0;
	signal(SIGINT, SIG_IGN);
	if (!isatty(0))
		write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	do {
		command_count++;
		line = NULL;
		size = 0;
		parser(line, size, command_count, av);

	} while (1);

	return (0);
}
