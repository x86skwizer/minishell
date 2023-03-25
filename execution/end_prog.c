/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_prog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:50:56 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/25 00:57:04 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

void	end_program(t_pars *cmd)
{
	if (cmd->input || cmd->delimiter)
	{
		close(cmd->fd_input);
		if (cmd->input)
			free(cmd->input);
		if (cmd->delimiter)
			free(cmd->delimiter);
	}
	if (cmd->output)
	{
		close(cmd->fd_output);
		free(cmd->output);
	}
	if (cmd->cmd)
		free_double(cmd->cmd);
	if (cmd->paths)
		free_double(cmd->paths);
}

char	*parent_process(t_list *list, char *str)
{
	t_data	data;
	//t_list	*tmp;

	data.i = 0;
	data.curr = list;
	while (data.i < g_global.nbr_cmd)
	{
		data.cmd = (t_pars *)data.curr->content;
		waitpid(g_global.pid[data.i], &g_global.exit_code, 0);
		end_program(data.cmd);
		data.curr = data.curr->next;
		// if (data.curr)
		// 	free(data.curr);
		// data.curr = tmp;
		data.i++;
	}
	//free(g_global.pid);
	free(str);
	return (NULL);
}
