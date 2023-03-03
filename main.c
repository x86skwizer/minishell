/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/03 20:16:27 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/parsing.h"
#include <signal.h>

void	handler(int num)
{
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	int		nbr;
	int		ipip;
	int		i;
	struct sigaction	sa;

	sa.sa_handler = handler;
  	sigemptyset (&sa.sa_mask);
  	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL); //Ctrl + /
	sigaction(SIGINT, &sa, NULL); // Ctrl + C

	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);
			else if (str == NULL) // Ctrl + D
			{
				write(1, "\n", 1);
				continue ;
			}
			else
				continue ;
			//Check for error and return nbr of cmds
			if (check_error_parsing(str))
			{
				printf("minishell: syntax error unexpected token\n");
				free(str);
				continue ;
			}

			// Parsing
			nbr = count_cmd(str);
			i = 0;
			ipip = 0;
			list = NULL;
			while (i < nbr)
			{
				
				ipip += fill_cmd_list(env, str + ipip, &list);
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