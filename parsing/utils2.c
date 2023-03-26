/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:50:14 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 22:55:43 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
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

char	*ft_trim(char *s, char c)
{
	char	**str;
	char	*tmp;
	char	*tmp1;
	int		i;

	i = 0;
	str = ft_split(s, c);
	tmp = ft_strdup(str[0]);
	i++;
	while (str[i])
	{
		tmp1 = tmp;
		tmp = ft_strjoin(tmp1, str[i]);
		free(tmp1);
		i++;
	}
	free_double(str);
	free (s);
	return (tmp);
}

int	input_file(t_pars **cmd, char *str, int i)
{
	int	start;

	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	if ((*cmd)->delimiter || ((*cmd)->input))
	{
		close((*cmd)->fd_input);
		if ((*cmd)->delimiter)
			free((*cmd)->delimiter);
		if ((*cmd)->input)
			free((*cmd)->input);
	}
	(*cmd)->input = ft_substr(str, start, i - start);
	(*cmd)->fd_input = open((*cmd)->input, O_RDONLY);
	if ((*cmd)->fd_input == -1)
		handle_error(errno);
	return (i);
}

int	pars_and_check(t_pars **cmd, char *str, int i, int j)
{
	int	start;
	int	inside_quote;

	start = i;
	inside_quote = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '|'))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			inside_quote = str[i];
			i++;
			while (str[i] && str[i] != inside_quote)
				i++;
			inside_quote = 0;
		}
		i++;
	}
	(*cmd)->cmd[j] = ft_substr(str, start, i - start);
	while (check_expansion((*cmd)->cmd[j]))
		expand_arg((&(*cmd)->cmd[j]));
	return (i);
}
