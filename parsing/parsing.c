/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:07:47 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 21:50:10 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	handle_quotes(t_pars **cmd, char *str, int *i, int *j)
{
	if (str[*i] == 34)
	{
		(*i) = double_quotes(cmd, str, *i, *j);
		(*j)++;
	}
	else if (str[*i] == 39)
	{
		(*i) = single_quotes(cmd, str, *i, *j);
		(*j)++;
	}
}

void	handle_redirections(t_pars **cmd, char *str, int *i)
{
	if (str[(*i)] == '>')
	{
		(*i)++;
		if (str[(*i)] == '>')
			(*i) = append_file(cmd, str, (*i));
		else
			(*i) = output_file(cmd, str, (*i));
	}
	else if (str[(*i)] == '<')
	{
		(*i)++;
		if (str[(*i)] == '<')
			(*i) = heredoc_open(cmd, str, (*i));
		else
			(*i) = input_file(cmd, str, (*i));
	}
}

int	split_arg(char *str, t_pars **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(*cmd)->cmd = malloc(sizeof(char *) * (count_arg(str) + 1));
	while (str[i] != '\0' && str[i] != '|')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == 34 || str[i] == 39)
			handle_quotes(cmd, str, &i, &j);
		else if (str[i] == '>' || str[i] == '<')
			handle_redirections(cmd, str, &i);
		else if (str[i] && str[i] != ' ' && str[i] != '|')
		{
			i = pars_and_check(cmd, str, i, j);
			j++;
		}
	}
	(*cmd)->cmd[j] = NULL;
	if (str[i] == '|')
		return (i + 1);
	return (0);
}

int	fill_cmd_list(char *str, t_list **list)
{
	t_pars	*cmd;
	t_list	*new;
	int		ipip;

	cmd = malloc(sizeof(t_pars));
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->delimiter = NULL;
	ipip = split_arg(str, &cmd);
	cmd->paths = arrange_paths();
	if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
		&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0])
		&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0])
		&& ft_strcmp("exit", cmd->cmd[0]))
		add_cmd_path(&cmd);
	new = ft_lstnew(cmd);
	ft_lstadd_back(list, new);
	return (ipip);
}
