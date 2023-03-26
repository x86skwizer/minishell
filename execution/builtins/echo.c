/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:07:14 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:43:26 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

int	ft_cmp_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] && (!ft_strcmp(args[1], "-n") || ft_cmp_n(args[1])))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (args[1] && !ft_cmp_n(args[1]) && ft_strcmp(args[1], "-n"))
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
