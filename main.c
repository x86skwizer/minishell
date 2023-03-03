/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/03 03:20:54 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	int		nbr;
	int		n;
	int		i;

	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);
			else
				continue ;
			//Check for error and return nbr of cmds
			if (check_error_parsing(str))
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				free(str);
				continue ;
			}

			// Parsing
			nbr = count_cmd(str);
			i = 0;
			n = 0;
			list = NULL;
			while (i < nbr)
			{
				
				n += fill_cmd_list(env, str + n, &list);
				i++;
			}
			// Test
			t_list	*curr;
			curr = list;
			while (curr != NULL)
			{
				i = 0;
				while (curr->cmd->cmd[i] != NULL)
				{
					printf("arg (%d) : |%s|\n", i, curr->cmd->cmd[i]);
					i++;
				}
				printf("input  : |%s|\n", curr->cmd->input);
				printf("output : |%s|\n", curr->cmd->output);
				printf("append : |%s|\n", curr->cmd->append);
				printf("delimiter : |%s|\n", curr->cmd->delimiter);
				curr = curr->next;
			}
			
			// Execution (one cmd)
			// if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
			// 		&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
			// 		&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
			// 		&& ft_strcmp("exit", cmd->cmd[0]))
			// {
			// 	cmd->pid = fork();
			// 	if (cmd->pid == -1)
			// 		handle_error(errno);
			// 	else if (cmd->pid == 0)
			// 	{
			// 		if (execve(cmd->cmd[0], cmd->cmd, env) == -1)
			// 			handle_error(errno);
			// 	}
			// 	wait(NULL);
			// 	free_double(cmd->cmd);
			// 	free(str);
			// }
			// else if (!ft_strcmp("echo", cmd->cmd[0]))
			// {
			// 	printf("Executing echo...\n");
			// 	builtin_echo(cmd->cmd);
			// }
			// else
			// 	printf("Found it!\n");
		}
	}
	return (0);
}