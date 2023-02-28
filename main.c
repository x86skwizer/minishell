/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/01 00:18:11 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	look_for_in(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] == ' ')
		i++;
	if (ft_strnstr(s2 + i, s1, 4))
		return (1);
	else
		return (0);
}

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
			if (look_for_in("echo", str)) // return index after echo in str
			{
				printf("Found echo !\n");
				continue ;
			}
			else
			{
			
				cmd->paths = arrange_paths(env);
				split_arg(str, &cmd);
				add_cmd_path(&cmd);
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