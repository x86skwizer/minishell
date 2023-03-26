/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:59:34 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 22:39:52 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

char	**get_paths(void)
{
	t_list	*tmp;
	t_env	*env;
	char	*path_var;
	char	**paths;

	path_var = NULL;
	tmp = g_global.env;
	while (tmp != NULL)
	{
		env = (t_env *)tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			path_var = ft_strdup(env->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	free(path_var);
	return (paths);
}

char	**arrange_paths(void)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = get_paths();
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

void	join_cmd_path(t_pars **cmd, char *tmp, char *path_cmd)
{
	free((*cmd)->cmd[0]);
	(*cmd)->cmd[0] = ft_strdup(path_cmd);
	free(tmp);
	free(path_cmd);
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
				join_cmd_path(cmd, tmp, path_cmd);
				return ;
			}
			free(path_cmd);
			i++;
		}
		free((*cmd)->cmd[0]);
		(*cmd)->cmd[0] = ft_strdup(tmp);
	}
	free(tmp);
}
