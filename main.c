/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 18:21:44 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include <readline/readline.h>
#include <readline/history.h>

t_merge	g_global;

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

void	fill_main(char **env, char *str)
{
	t_data	data;
	t_list	*list;

	list = NULL;
	data.i = 0;
	data.ipip = 0;
	g_global.nbr_cmd = count_cmd(str);
	while (data.i < g_global.nbr_cmd)
	{
		data.ipip += fill_cmd_list(str + data.ipip, &list);
		data.i++;
	}
	execute(list, env);
	parent_process(list);
	if (list)
	{
		free_list(list);
		list = NULL;
	}
	free (str);
}

void	main_loop(char **env, char *str)
{
	int		i;

	while (1)
	{
		str = readline("minishell$  ");
		if (str && *str)
			add_history(str);
		else if (str == NULL)
			exit(0);
		else
		{
			free(str);
			continue ;
		}
		i = check_error_parsing(str);
		if (i)
		{
			printf("minishell: syntax error unexpected token\n");
			free(str);
			continue ;
		}
		fill_main(env, str);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	signal(SIGINT, int_handler);
	signal(SIGQUIT, quit_handler);
	g_global.exit_code = 0;
	if (ac >= 1)
	{
		av[1] = NULL;
		env_fill(env);
		str = NULL;
		main_loop(env, str);
	}
	return (0);
}
