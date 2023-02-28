/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 02:25:12 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/28 03:02:33 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(int static_code)
{
	perror("minishell");
	exit(static_code);
}

void	free_double(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
	{
		free(pointer[i]);
		i++;
	}
	free (pointer);
	pointer = NULL;
}
