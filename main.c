/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/16 18:31:53 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include <readline/readline.h>
#include <readline/history.h>

t_merge	*my_global;

// void	int_handler(int sig)
// {
// 	(void)sig;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	my_global->exit_code  = 1;

// }

// void	quit_handler(int sig)
// {
// 	(void)sig;
// 	rl_on_new_line();
// 	rl_redisplay();
// }

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	t_data	data;

	// signal(SIGINT, int_handler);
	// signal(SIGQUIT, quit_handler);
	my_global = malloc(sizeof(t_merge));
	my_global->env = malloc(sizeof(t_list));
	env_fill(env);
	if (ac >= 1)
	{
		av[1] = NULL;
		my_global->exit_code = 0;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);
			else
				continue ;
			my_global->exit_code = check_error_parsing(str);
			if (my_global->exit_code)
			{
				printf("minishell: syntax error unexpected token\n");
				free(str);
				continue ;
			}
			data.i = 0;
			data.ipip = 0;
			list = NULL;
			my_global->nbr_cmd = count_cmd(str);
			while (data.i < my_global->nbr_cmd)
			{
				data.ipip += fill_cmd_list(env, str + data.ipip, &list);
				data.i++;
			}
			execute(list, env);
		}
	}
	return (0);
}