/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:16:19 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/04 07:23:46 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_listp	*ft_lstlast_cmd(t_listp *lst)
{
	t_listp	*curr;
	t_listp	*aux;

	curr = lst;
	if (curr == NULL)
		return (NULL);
	while (curr != NULL)
	{
		aux = curr;
		curr = curr->next;
	}
	return (aux);
	
}