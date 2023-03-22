/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/22 07:36:52 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include <readline/readline.h>
#include <readline/history.h>

t_merge	*g_global;

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	t_data	data;

	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);
	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			g_global = malloc(sizeof(t_merge));
			g_global->exit_code = 0;
			g_global->env = malloc(sizeof(t_list));
			env_fill(env);
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);
			else
				continue ;
			g_global->exit_code = check_error_parsing(str);
			if (g_global->exit_code)
			{
				printf("minishell: syntax error unexpected token\n");
				free(str);
				continue ;
			}
			list = NULL;
			data.i = 0;
			data.ipip = 0;
			g_global->nbr_cmd = count_cmd(str);
			while (data.i < g_global->nbr_cmd)
			{
				data.ipip += fill_cmd_list(str + data.ipip, &list);
				data.i++;
			}
			execute(list, env);
			str = parent_process(list, str);
		}
	}
	return (0);
}
