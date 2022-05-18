#include "sh.h"

void sigintH(int signum)
{
	if (signum == SIGINT)
	{
		_write_char('\n');
		write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	}
}
