/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:07:34 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:37:10 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

void	tenv_free(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

int	builtin_unset(char **args)
{
	t_list	*tmp;
	t_env	*env_tmp;
	t_list	*parent;
	int		i;

	i = 1;
	tmp = g_global.env;
	while (args[i])
	{
		tmp = g_global.env;
		parent = NULL;
		while (tmp)
		{
			env_tmp = (t_env *)(tmp->content);
			if (ft_strcmp(env_tmp->key, args[i]) == 0)
			{
				if (parent)
					parent->next = tmp->next;
				else
					g_global.env = tmp->next;
				ft_lstdelone(tmp, tenv_free);
				break ;
			}
			parent = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	tmp = g_global.env;
	return (0);
}
