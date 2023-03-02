/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/02 01:22:56 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_error_parsing(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (-1);
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
			return (-1);
		i++;
	}
	i = len - 1;
	while (str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (-1);
	else if (str[i] == '>')
		return (-1);
	else if (str[i] == '<')
		return (-1);
	return (0);
}

int	count_cmd(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 1;
	while (str[i])
	{
		if (str[i] == '|')
			nbr++;
		i++;
	}
	return (nbr);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_pars	*cmd;
	int		nbr;

	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);
			
			//Check for error and return nbr of cmds
			if (check_error_parsing(str))
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				free(str);
				continue ;
			}

			// Parsing
			nbr = count_cmd(str);
			cmd = malloc(sizeof(t_pars) * nbr); //Alloc nbr of cmds
			split_arg(str, &cmd); //for every cmd 
			cmd->paths = arrange_paths(env);
			//for every cmd
			if (ft_strcmp("echo", cmd->cmd[0]) && ft_strcmp("cd", cmd->cmd[0])
					&& ft_strcmp("pwd", cmd->cmd[0]) && ft_strcmp("export", cmd->cmd[0]) 
					&& ft_strcmp("unset", cmd->cmd[0]) && ft_strcmp("env", cmd->cmd[0]) 
					&& ft_strcmp("exit", cmd->cmd[0]))
				add_cmd_path(&cmd);



			// Test multi cmd
			// n = 0;
			// while (n < nbr)
			// {
			// 	i = 0;
			// 	printf("cmd : |%s|\n", cmd[n]->cmd[i++]);
			// 	while (cmd[n]->cmd[i])
			// 	{
			// 		printf("arg (%d) : |%s| ;; ", i, cmd[n]->cmd[i]);
			// 		i++;
			// 	}
			// 	printf(" ;; input (%d) : |%s|", i, cmd[n]->input);
			// 	printf(" ;; output (%d) : |%s|", i, cmd[n]->output);
			// 	printf(" ;; append (%d) : |%s|", i, cmd[n]->append);
			// 	printf(" ;; delimiter (%d) : |%s|", i, cmd[n]->delimiter);
			// 	printf("\n");
			// 	n++;
			// }
			
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