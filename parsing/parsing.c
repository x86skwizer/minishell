/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:07:47 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/08 07:59:17 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

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
		if(str[i] == 34) // "
		{
			i++;
			while (str[i] && str[i] != 34) // if !str[i] print error
				i++;
			nbr++;
		}
		else if(str[i] == 39) // '
		{
			i++;
			while (str[i] && str[i] != 39) // if !str[i] print error
				i++;
			nbr++;
		}
		else if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
			{
				i++;
				while (str[i] && str[i] == ' ')
					i++;
				while (str[i] && str[i] != ' ')
					i++;
			}
			else
			{
				while (str[i] && str[i] == ' ')
					i++;
				while (str[i] && str[i] != ' ')
					i++;
			}
		}
		else if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				i++;
				while (str[i] && str[i] == ' ')
					i++;
				while (str[i] && str[i] != ' ')
					i++;
			}
			else
			{
				while (str[i] && str[i] == ' ')
					i++;
				while (str[i] && str[i] != ' ')
					i++;
			}
		}
		else if (str[i] && str[i] != ' '&& str[i] != '|')
		{
			while (str[i] && str[i] != ' ' && str[i] != '|') // if !str[i] print error
				i++;
			nbr++;
		}
	}
	return (nbr);
}

int	split_arg(char *str, t_pars **cmd)
{
	int		i;
	int		j;
	int		start;
	int		nbr;

	i = 0;
	j = 0;
	nbr = count_arg(str);
	(*cmd)->cmd = malloc(sizeof(char *) * (nbr + 1));
	while (str[i] != '\0' && str[i] != '|')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if(str[i] == 34) // "
		{
			i++;
			start = i;
			while (str[i] && str[i] != 34)
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			j++;
			i++;
		}
		else if(str[i] == 39) // '
		{
			i++;
			start = i;
			while (str[i] && str[i] != 39)
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			i++;
			j++;
		}
		else if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
			{
				i++;
				while (str[i] && str[i] == ' ')
					i++;
				start = i;
				while (str[i] && str[i] != ' ')
					i++;
				(*cmd)->append = ft_substr(str, start, i - start);
			}
			else
			{
				while (str[i] && str[i] == ' ')
					i++;
				start = i;
				while (str[i] && str[i] != ' ')
					i++;
				(*cmd)->output = ft_substr(str, start, i - start);
			}
		}
		else if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				i++;
				while (str[i] && str[i] == ' ')
					i++;
				start = i;
				while (str[i] && str[i] != ' ')
					i++;
				(*cmd)->delimiter = ft_substr(str, start, i - start);
			}
			else
			{
				while (str[i] && str[i] == ' ')
					i++;
				start = i;
				while (str[i] && str[i] != ' ')
					i++;
				(*cmd)->input = ft_substr(str, start, i - start);
			}
		}
		else if (str[i] && str[i] != ' ' && str[i] != '|')
		{
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '|')
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			j++;
		}
	}
	(*cmd)->cmd[j] = NULL;
	if (str[i] == '|')
		return (i + 1);
	return (0);
}

int	fill_cmd_list(char **env, char *str, t_list **list)
{
	t_pars	*cmd;
	t_list	*new;
	int		ipip;

	cmd = malloc(sizeof(t_pars));
	ipip = split_arg(str, &cmd);
	cmd->paths = arrange_paths(env);
	if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
			&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
			&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
			&& ft_strcmp("exit", cmd->cmd[0]))
		add_cmd_path(&cmd);
	new = ft_lstnew(cmd);
	ft_lstadd_back(list, new);
	return (ipip);
}