/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/01 01:36:42 by yamrire          ###   ########.fr       */
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
			cmd = malloc(sizeof(t_pars));
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);

			// Parsing
			cmd->paths = arrange_paths(env);
			split_arg(str, &cmd);
			if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0]) 
				&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
				&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) && ft_strcmp("exit", cmd->cmd[0]))
				add_cmd_path(&cmd);
			else
			{
				printf("found it !\n");
				continue ;
			}
			int i = 0;
			while (cmd->cmd[i])
			{
				printf("arg (%d) : |%s|\n", i, cmd->cmd[i]);
				i++;
			}
			printf("input  : |%s|\n", cmd->input);
			printf("output : |%s|\n", cmd->output);
			printf("append : |%s|\n", cmd->append);
			printf("delimiter : |%s|\n", cmd->delimiter);
			
			// Execution
			// cmd->pid = fork();
			// if (cmd->pid == -1)
			// 	handle_error(errno);
			// else if (cmd->pid == 0)
			// {
			// 	if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
			// 		handle_error(errno);
			// }
			// wait(NULL);
			// free_double(cmd->cmd);
			// free(str);
		}
	}
	return (0);
}