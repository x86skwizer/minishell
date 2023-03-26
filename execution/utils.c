/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:27:06 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 03:53:47 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	check_entry(t_pars *cmd)
{
	if ((cmd->input) || (cmd->delimiter))
	{
		if ((g_global.nbr_cmd == 1 && (!ft_strcmp("echo", cmd->cmd[0]) || !ft_strcmp("cd", cmd->cmd[0])
        || !ft_strcmp("pwd", cmd->cmd[0]) || !ft_strcmp("export", cmd->cmd[0])
        || !ft_strcmp("unset", cmd->cmd[0]) || !ft_strcmp("env", cmd->cmd[0])
        || !ft_strcmp("exit", cmd->cmd[0]))))
            g_global.fd_tmpin = dup(0); 
		dup2(cmd->fd_input, 0);
		close(cmd->fd_input);
	}
	if (cmd->output)
	{
		if ((g_global.nbr_cmd == 1 && (!ft_strcmp("echo", cmd->cmd[0]) || !ft_strcmp("cd", cmd->cmd[0])
		|| !ft_strcmp("pwd", cmd->cmd[0]) || !ft_strcmp("export", cmd->cmd[0])
		|| !ft_strcmp("unset", cmd->cmd[0]) || !ft_strcmp("env", cmd->cmd[0])
		|| !ft_strcmp("exit", cmd->cmd[0]))))
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
