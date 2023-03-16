#include "../minishell.h"
#include "../../merge.h"

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
		i++; 
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (args[1] && ft_strcmp(args[1], "-n"))
		ft_putstr_fd("\n", 1);
	return (0);
}
