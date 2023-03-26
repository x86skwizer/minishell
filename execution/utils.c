/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:27:06 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:21:44 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd)
		|| !ft_strcmp("exit", cmd))
		return (1);
	else
		return (0);
}

void	check_entry(t_pars *cmd)
{
	if ((cmd->input) || (cmd->delimiter))
	{
		if (g_global.nbr_cmd == 1 && is_builtin(cmd->cmd[0]))
			g_global.fd_tmpin = dup(0);
		dup2(cmd->fd_input, 0);
		close(cmd->fd_input);
	}
	if (cmd->output)
	{
		if (g_global.nbr_cmd == 1 && is_builtin(cmd->cmd[0]))
			g_global.fd_tmpout = dup(1);
		dup2(cmd->fd_output, 1);
		close(cmd->fd_output);
	}
}

void	init_pipe(void)
{
	if (g_global.fd_tmp != -1)
		close(g_global.fd_tmp);
	g_global.fd_tmp = dup(g_global.fd_pip[0]);
	close(g_global.fd_pip[0]);
	close(g_global.fd_pip[1]);
}

void	pipline(void)
{
	close(g_global.fd_pip[0]);
	dup2(g_global.fd_pip[1], 1);
	close(g_global.fd_pip[1]);
}

void	dup_tmp(void)
{
	dup2(g_global.fd_tmp, 0);
	close(g_global.fd_tmp);
}
