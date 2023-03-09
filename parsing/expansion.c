/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 07:38:56 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/09 07:59:02 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

int	check_expansion(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '$') && ((cmd[i + 1] >= 65 && cmd[i + 1] <= 90)
			|| (cmd[i + 1] >= 97 && cmd[i + 1] <= 122)))
			return (1);
		i++;
	}
	return (0);
}

int	check_env_var(char *s)
{
	t_list	*list;
	t_env	*env;


	list = my_global->env;
	while (list)
	{
		env = (t_env *)list->content;
		if (ft_strcmp(env->key, s) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

void	expand(char **s)
{
	t_list	*list;
	t_env	*env;


	list = my_global->env;
	while (list)
	{
		env = (t_env *)list->content;
		if (ft_strcmp(env->key, *s) == 0)
		{
			free(*s);
			*s = ft_strdup(env->value);
			return ;
		}
		list = list->next;
	}
}

void	expand_arg(char **arg)
{
	char	*s1;
	char	*s2;
	char	*s3;
	int	start;
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		if (((*arg)[i] == '$') && (((*arg)[i + 1] >= 65 && (*arg)[i + 1] <= 90)
			|| ((*arg)[i + 1] >= 97 && (*arg)[i + 1] <= 122)))
		{
			i++;
			s1 = ft_substr((*arg), 0, i - 1);
			start = i;
			while (((*arg)[i] >= 65 && (*arg)[i] <= 90) || ((*arg)[i] >= 97 && (*arg)[i] <= 122))
				i++;
			s2 = ft_substr((*arg), start, i - start);
			s3 = ft_substr((*arg), i, ft_strlen((*arg)) - i);
			
			if (check_env_var(s2))
			{
				free((*arg));
				expand(&s2);
				(*arg) = ft_strjoin(ft_strjoin(s1, s2), s3);
				free(s1);
				free(s2);
				free(s3);
				break ;
			}
			else
			{
				free((*arg));
				(*arg) = ft_strjoin(s1, s3);
				free(s1);
				free(s2);
				free(s3);
				break ;
			}
		}
		i++;
	}
}