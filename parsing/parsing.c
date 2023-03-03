/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:07:47 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/03 19:59:29 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	add_cmd_path(t_pars **cmd)
{
	char	*path_cmd;
	char	*tmp;
	int		i;

	if (!(*cmd)->paths)
		return ;
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