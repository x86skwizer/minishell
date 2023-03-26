/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:49:41 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 22:18:55 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	handle_quotes_count(char *str, int *i, int *nbr)
{
	if (str[(*i)] == 34)
	{
		(*i)++;
		while (str[(*i)] && str[(*i)] != 34)
			(*i)++;
		(*nbr)++;
	}
	else if (str[(*i)] == 39)
	{
		(*i)++;
		while (str[(*i)] && str[(*i)] != 39)
			(*i)++;
		(*nbr)++;
	}
}

int	skip(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	handle_redirection_count(char *str, int *i)
{
	if (str[(*i)] == '>')
	{
		(*i)++;
		if (str[(*i)] == '>')
			(*i) = skip(str, (*i) + 1);
		else
			(*i) = skip(str, (*i));
	}
	else if (str[(*i)] == '<')
	{
		(*i)++;
		if (str[(*i)] == '<')
			(*i) = skip(str, (*i) + 1);
		else
			(*i) = skip(str, (*i));
	}
}

int	count_arg(char *str)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] != '\0' && str[i] != '|')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == 34 || str[i] == 39)
			handle_quotes_count(str, &i, &nbr);
		else if (str[i] == '>' || str[i] == '<')
			handle_redirection_count(str, &i);
		else if (str[i] && str[i] != ' ' && str[i] != '|')
		{
			while (str[i] && str[i] != ' ' && str[i] != '|')
				i++;
			nbr++;
		}
	}
	return (nbr);
}
