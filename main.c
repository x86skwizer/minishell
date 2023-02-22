/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/22 04:22:33 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_cmd	cmd;

	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);

			// Parsing
			cmd.paths = arrange_paths(env);
			cmd.cmd = get_cmd_options(&cmd, str);

			// Execution
			cmd.pid = fork();
			if (cmd.pid == -1)
				handle_error(errno);
			else if (cmd.pid == 0)
			{
				if (execve(cmd.cmd[0], cmd.cmd, env) == -1)
					handle_error(errno);
			}
			wait(NULL);
			free_double(cmd.cmd);
			free(str);
		}
	}
	return (0);
}