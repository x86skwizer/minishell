/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:20:19 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:21:36 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	check_position(t_pars *cmd, int i)
{
	if (i == 0)
	{
		if (g_global.nbr_cmd > 1)
			pipline();
		check_entry(cmd);
	}
	else if (i == g_global.nbr_cmd - 1)
	{
		dup_tmp();
		check_entry(cmd);
	}
	else if (i > 0 && i < g_global.nbr_cmd - 1)
	{
		pipline();
		dup_tmp();
		check_entry(cmd);
	}
}
