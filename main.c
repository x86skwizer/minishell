/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/07 04:12:30 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"

t_merge	*my_global;

void	builtin_env(void)
{
	t_list	*curr;

	curr = my_global->env;
	while (curr)
	{
		t_env *env = (t_env *)curr->content;
		printf("%s=", env->key);
		printf("%s\n", env->value);
		curr = curr->next;
	}
}

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
			
			// Execution (one cmd)
			t_list	*curr = list;
			t_pars *cmd = (t_pars *)curr->content;
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
				builtin_echo(cmd->cmd);
			else if (!ft_strcmp("cd", cmd->cmd[0]))
				builtin_cd(cmd->cmd);
			else if (!ft_strcmp("pwd", cmd->cmd[0]))
				builtin_pwd();
			else if (!ft_strcmp("env", cmd->cmd[0]))
				builtin_env();
			else
				printf("Found it!\n");
		}
	}
	return (0);
}