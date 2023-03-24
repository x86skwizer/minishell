/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_prog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:50:56 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/24 21:35:44 by yamrire          ###   ########.fr       */
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

	data.curr = list;
	while (data.curr)
	{
		data.cmd = (t_pars *)data.curr->content;
		waitpid(-1, &g_global.exit_code, 0);
		end_program(data.cmd);
		data.curr = data.curr->next;
	}
	free(g_global.pid);
	
	free(str);
	return (NULL);
}
