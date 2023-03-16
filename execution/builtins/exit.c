#include "../minishell.h"
#include "../../merge.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *s)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '-')
		neg = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res * neg);
}

int	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (ft_isdigit(args[1][0]))
			exit_code = ft_atoi(args[1]);
		else
		{
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			return (255);
		}
	}
	exit(exit_code);
}
