/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:25:12 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/22 07:24:49 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	handle_error(int static_code)
{
	perror("minishell");
	g_global->exit_code = static_code;
}

void	exit_error(int static_code)
{
	perror("minishell");
	g_global->exit_code = static_code;
	exit(static_code);
}

void	free_double(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free (pointer);
	pointer = NULL;
}

int	check_error_parsing(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (-1);
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (-1);
		i++;
	}
	i = len - 1;
	while (str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (-1);
	else if (str[i] == '>')
		return (-1);
	else if (str[i] == '<')
		return (-1);
	return (0);
}

int	count_cmd(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 1;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		if (str[i] == '|')
			nbr++;
		i++;
	}
	return (nbr);
}
