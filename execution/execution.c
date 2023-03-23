/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:47:09 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/22 08:23:47 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	start_exec(int i)
{
	g_global.pid[i] = fork();
	if (g_global.pid[i] == -1)
		handle_error(errno);
}

void	execute_builtins(char **cmd)
{
	if (!ft_strcmp("echo", cmd[0]))
		g_global.exit_code = builtin_echo(cmd);
	else if (!ft_strcmp("cd", cmd[0]))
		g_global.exit_code = builtin_cd(cmd);
	else if (!ft_strcmp("pwd", cmd[0]))
		g_global.exit_code = builtin_pwd();
	else if (!ft_strcmp("env", cmd[0]))
		g_global.exit_code = builtin_env();
	else if (!ft_strcmp("export", cmd[0]))
		g_global.exit_code = builtin_export(cmd);
	else if (!ft_strcmp("unset", cmd[0]))
		g_global.exit_code = builtin_unset(cmd);
	else if (!ft_strcmp("exit", cmd[0]))
		g_global.exit_code = builtin_exit(cmd);
	if (g_global.exit_code)
		exit_error(g_global.exit_code);
	exit(g_global.exit_code);
}

void	execute_one_cmd(t_pars *cmd, char **env, int i)
{
	check_position(cmd, i);
	if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
		&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0])
		&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0])
		&& ft_strcmp("exit", cmd->cmd[0]))
	{
		if (execve(cmd->cmd[0], cmd->cmd, env))
			exit_error(errno);
	}
	else
		execute_builtins(cmd->cmd);
}

void	execute(t_list *list, char **env)
{
	t_list	*curr;
	t_pars	*cmd;
	int		i;

	i = 0;
	curr = list;
	g_global.fd_tmp = -1;
	g_global.pid = malloc(g_global.nbr_cmd * sizeof(pid_t));
	while (i < g_global.nbr_cmd)
	{
		cmd = (t_pars *)curr->content;
		if (g_global.nbr_cmd > 1)
		{
			if (i <= g_global.nbr_cmd - 1 && i > 0)
				init_pipe();
			if (i < g_global.nbr_cmd - 1)
				pipe(g_global.fd_pip);
		}
		start_exec(i);
		if (g_global.pid[i] == 0)
			execute_one_cmd(cmd, env, i);
		curr = curr->next;
		i++;
	}
}
