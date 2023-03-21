/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:07:47 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/21 04:38:56 by yamrire          ###   ########.fr       */
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
		if(str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
				i++;
			nbr++;
		}
		else if(str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
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
		else if (str[i] && str[i] != ' ' && str[i] != '|')
		{
			while (str[i] && str[i] != ' ' && str[i] != '|')
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
		if(str[i] == 34)
		{
			i++;
			start = i;
			while (str[i] && str[i] != 34)
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			while (check_expansion((*cmd)->cmd[j]))
				expand_arg((&(*cmd)->cmd[j]));
			j++;
			i++;
		}
		else if(str[i] == 39)
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
				if ((*cmd)->output)
				{
					close((*cmd)->fd_output);
					free((*cmd)->output);
				}
				(*cmd)->output = ft_substr(str, start, i - start);
				(*cmd)->fd_output = open((*cmd)->output, O_APPEND | O_CREAT | O_RDWR, 0644);
				if ((*cmd)->fd_output == -1)
					handle_error(errno);
			}
			else
			{
				while (str[i] && str[i] == ' ')
					i++;
				start = i;
				while (str[i] && str[i] != ' ')
					i++;
				if ((*cmd)->output)
				{
					close((*cmd)->fd_output);
					free((*cmd)->output);
				}
				(*cmd)->output = ft_substr(str, start, i - start);
				(*cmd)->fd_output = open((*cmd)->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if ((*cmd)->fd_output == -1)
					handle_error(errno);
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
				if ((*cmd)->delimiter || ((*cmd)->input))
				{
					close((*cmd)->fd_input);
					if ((*cmd)->delimiter)
						free((*cmd)->delimiter);
					if ((*cmd)->input)
						free((*cmd)->delimiter);
				}
				(*cmd)->delimiter = ft_substr(str, start, i - start);
				(*cmd)->fd_input = open("/tmp/.here_doc", O_APPEND | O_CREAT | O_RDWR | O_TRUNC, 0644);
				here_doc(*cmd);
				close((*cmd)->fd_input);
				(*cmd)->fd_input = open("/tmp/.here_doc", O_RDONLY);
			}
			else
			{
				while (str[i] && str[i] == ' ')
					i++;
				start = i;
				while (str[i] && str[i] != ' ')
					i++;
				if ((*cmd)->input)
				{
					close((*cmd)->fd_input);
					free((*cmd)->input);
				}
				(*cmd)->input = ft_substr(str, start, i - start);
				(*cmd)->fd_input = open((*cmd)->input, O_RDONLY);
				if ((*cmd)->fd_input == -1)
					handle_error(errno);
			}
		}
		else if (str[i] && str[i] != ' ' && str[i] != '|')
		{
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '|')
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			while (check_expansion((*cmd)->cmd[j]))
				expand_arg((&(*cmd)->cmd[j]));
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