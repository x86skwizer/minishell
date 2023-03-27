/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:51:47 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/27 00:56:24 by yamrire          ###   ########.fr       */
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

void	expand_question_mark(char **s)
{
	char	*s1;
	char	*s2;

	s1 = ft_itoa(g_global.exit_code);
	s2 = ft_strdup((*s) + 1);
	free(*s);
	(*s) = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
}
