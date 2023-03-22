/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 05:16:19 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/22 07:16:39 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr;
	t_list	*aux;

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
