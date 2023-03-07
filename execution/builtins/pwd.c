#include "../minishell.h"
#include "../../merge.h"

void builtin_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
}

// int main(int argc, char **argv)
// {
//     builtin_pwd(void);
//     return (0);
// }
