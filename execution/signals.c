#include "../merge.h"
#include <readline/readline.h>
#include <readline/history.h>

void	int_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global.exit_code = 1;
}

void	quit_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}
