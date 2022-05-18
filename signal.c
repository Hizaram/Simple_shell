#include "sh.h"

/**
 * sigintH - ignores the Ctrl+C command
 * @signum: command fed into it
 */

void sigintH(int signum)
{
	if (signum == SIGINT)
	{
		_write_char('\n');
		write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	}
}
