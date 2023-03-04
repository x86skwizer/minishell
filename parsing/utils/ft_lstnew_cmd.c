/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:16:10 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/04 04:53:22 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_listp	*ft_lstnew_cmd(t_pars *cmd)
{
	t_listp	*new_elem;

	new_elem = malloc(sizeof(t_listp));
	if (new_elem == NULL)
		return (NULL);
	new_elem->cmd = cmd;
	new_elem->next = NULL;
	return (new_elem);
}
