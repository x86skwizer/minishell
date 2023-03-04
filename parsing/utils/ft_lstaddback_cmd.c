/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:59:05 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/04 07:15:39 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	ft_lstaddback_cmd(t_listp **lst, t_listp *new)
{
	t_listp	*curr;

	if (*lst == 0x00)
	{
		*lst = new;
		return ;
	}
	curr = ft_lstlast_cmd(*lst);
	curr->next = new;
}