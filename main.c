/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/12 01:18:42 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"

t_merge	*my_global;

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	t_data	data;

	// To Do : Handle Signals
	my_global = malloc(sizeof(t_merge));
	env_fill(env); // Fill linked list with env variables (key, value)
	// Start Program
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
			if (check_error_parsing(str))
			{
				printf("minishell: syntax error unexpected token\n");
				free(str);
				continue ;
			}
			// Parsing
			data.i = 0;
			data.ipip = 0;
			list = NULL;
			data.nbr = count_cmd(str);
			while (data.i < data.nbr)
			{
				data.ipip += fill_cmd_list(env, str + data.ipip, &list);
				data.i++;
			}
			
			// Test Parsing
			// t_list	*curr = list;
			// while (curr)
			// {
			// 	t_pars *cmd = (t_pars *)curr->content;
			// 	int	i = 0;
			// 	printf("cmd : %s\n", cmd->cmd[i++]);
			// 	while (cmd->cmd[i])
			// 	{
			// 		printf("arg (%d) : %s\n",i, cmd->cmd[i]);
			// 		i++;
			// 	}
			// 	printf("input : %s\n", cmd->input);
			// 	printf("output : %s\n", cmd->output);
			// 	printf("append : %s\n", cmd->append);
			// 	printf("delimiter : %s\n", cmd->delimiter);
			// 	printf("================================\n");
			// 	curr = curr->next;
			// }
	
			// Execute first cmd
			execute(list, str, env, data.nbr);
		}
	}
	return (0);
}