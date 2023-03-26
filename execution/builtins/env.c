/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:07:17 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:07:19 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

int	builtin_env(void)
{
	t_list		*tmp;
	t_env		*tmp_content;

	tmp = g_global.env;
	while (tmp)
	{
		tmp_content = (t_env *)tmp->content;
		if (tmp_content->value)
		{
			ft_putstr_fd(tmp_content->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(tmp_content->value, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	return (0);
}
