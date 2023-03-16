/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/16 07:14:58 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"

t_merge	*my_global;

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_list	*list;
	t_data	data;

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