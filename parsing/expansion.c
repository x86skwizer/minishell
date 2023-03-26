/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 07:38:56 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:47:02 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

int	check_expansion(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '$') && (((cmd[i + 1] >= 65 && cmd[i + 1] <= 90)
					|| (cmd[i + 1] >= 97 && cmd[i + 1] <= 122)
					|| cmd[i + 1] == '_'
					|| cmd[i + 1] == '?')))
			return (1);
		i++;
	}
	return (0);
}

int	check_env_var(char *s)
{
	t_list	*list;
	t_env	*env;

	if (s[0] == '?')
		return (1);
	list = g_global.env;
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
	char	*s1;
	char	*s2;

	if ((*s)[0] == '?')
	{
		s1 = ft_itoa(g_global.exit_code);
		s2 = ft_strdup((*s) + 1);
		free(*s);
		(*s) = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	list = g_global.env;
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
	char	*s4;
	int		start;
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if (((*arg)[i] == '$') && ((((*arg)[i + 1] >= 65 && (*arg)[i + 1] <= 90)
			|| ((*arg)[i + 1] >= 97 && (*arg)[i + 1] <= 122))
			|| (*arg)[i + 1] == '_' || (*arg)[i + 1] == '?'))
		{
			i++;
			s1 = ft_substr((*arg), 0, i - 1);
			start = i;
			while ((((*arg)[i] >= 65 && (*arg)[i] <= 90)
					|| ((*arg)[i] >= 97 && (*arg)[i] <= 122))
					|| (*arg)[i] == '_' || (*arg)[i] == '?')
				i++;
			s2 = ft_substr((*arg), start, i - start);
			s3 = ft_substr((*arg), i, ft_strlen((*arg)) - i);
			if (check_env_var(s2))
			{
				free((*arg));
				expand(&s2);
				s4 = ft_strjoin(s1, s2);
				(*arg) = ft_strjoin(s4, s3);
				free(s1);
				free(s2);
				free(s3);
				free(s4);
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
