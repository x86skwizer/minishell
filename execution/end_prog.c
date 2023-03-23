/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_prog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 04:50:56 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/22 19:28:44 by yamrire          ###   ########.fr       */
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

	data.i = 0;
	data.curr = list;
	while (data.i < g_global.nbr_cmd)
	{
		data.cmd = (t_pars *)data.curr->content;
		end_program(data.cmd);
		waitpid(-1, &g_global.exit_code, 0);
		data.i++;
		data.curr = data.curr->next;
	}
	free(g_global.pid);
	ft_lstclear(&(g_global.env), free);
	free(str);
	return (NULL);
}
