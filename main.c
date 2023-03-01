/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/01 04:31:57 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_pars	*cmd;

	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);
			
			//Check for error and return nbr of cmds
			

			// Parsing
			cmd = malloc(sizeof(t_pars)); //Alloc nbr of cmds
			split_arg(str, &cmd); //for every cmd 
			cmd->paths = arrange_paths(env);
			//for every cmd
			if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
					&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
					&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
					&& ft_strcmp("exit", cmd->cmd[0]))
				add_cmd_path(&cmd);
			
			// Execution
			if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
					&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
					&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
					&& ft_strcmp("exit", cmd->cmd[0]))
			{
				cmd->pid = fork();
				if (cmd->pid == -1)
					handle_error(errno);
				else if (cmd->pid == 0)
				{
					if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
						handle_error(errno);
				}
				wait(NULL);
				free_double(cmd->cmd);
				free(str);
			}
			else if (!ft_strcmp("echo", cmd->cmd[0]))
			{
				printf("Executing echo...\n");
				builtin_echo(cmd->cmd);
			}
			else
				printf("Found it!\n");
		}
	}
	return (0);
}