/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:07:47 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/28 17:55:14 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (str[i] && str[i] != ' ')
		{
			while (str[i] && str[i] != ' ') // if !str[i] print error
				i++;
			nbr++;
		}
	}
	//return 0 if no valuable cmd
	return (nbr);
}

void	split_arg(char *str, t_cmd **cmd)
{
	int		i;
	int		j;
	int		start;
	int		nbr;

	i = 0;
	j = 0;
	nbr = count_arg(str);
	// cmd->cmd = malloc(sizeof(char *) * (count_arg(str) + 1));
	(*cmd)->cmd = malloc(sizeof(char *) * (nbr + 1));
	while (str[i] != '\0' && str[i] != '|')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if(str[i] == 34) // "
		{
			i++;
			start = i;
			while (str[i] && str[i] != 34) // if !str[i] print error
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			j++;
			i++;
		}
		else if(str[i] == 39) // '
		{
			i++;
			start = i;
			while (str[i] && str[i] != 39) // if !str[i] print error
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
		else if (str[i] && str[i] != ' ')
		{
			start = i;
			while (str[i] && str[i] != ' ') // if !str[i] print error
				i++;
			(*cmd)->cmd[j] = ft_substr(str, start, i - start);
			j++;
		}
	}
	(*cmd)->cmd[j] = NULL;
}

char	**get_paths(char **envp)
{
	char	*path_var;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		path_var = ft_strnstr(envp[i], "PATH=", 5);
		if (path_var)
		{
			path_var = ft_substr(path_var, 5, ft_strlen(path_var) - 5);
			break ;
		}
		i++;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	free(path_var);
	return (paths);
}

char	**arrange_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	return (paths);
}

void	add_cmd_path(t_cmd **cmd)
{
	char	*path_cmd;
	char	*tmp;
	int		i;

	if (!(*cmd)->paths)
		return ;
	// Parse Single & Double Quotes
	tmp = ft_strdup((*cmd)->cmd[0]);
	if (!(ft_strchr((*cmd)->cmd[0], '/')))
	{
		i = 0;
		while ((*cmd)->paths[i])
		{
			path_cmd = ft_strjoin((*cmd)->paths[i], (*cmd)->cmd[0]);
			if (access(path_cmd, F_OK | X_OK) == 0)
			{
				free((*cmd)->cmd[0]);
				(*cmd)->cmd[0] = ft_strdup(path_cmd);
				free(tmp);
				free(path_cmd);
				return ;
			}
			free(path_cmd);
			i++;
		}
		free((*cmd)->cmd[0]);
		(*cmd)->cmd[0] = ft_strdup(tmp);
		free(tmp);
	}
	
}