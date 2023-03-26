/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 22:42:12 by yamrire          ###   ########.fr       */
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

int    contains_spaces(char *str)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int    check_cmd(char *str)
{
    add_history(str);
    if (contains_spaces(str))
    {
        free(str);
        return (1);
    }
    return (0);
}

void    main_loop(char **env, char *str)
{
    while (1)
    {
        str = readline("minishell$  ");
        if (str && *str)
        {    
            if (check_cmd(str))
                continue ;
        }
        else if (str == NULL)
            exit(0);
        else
        {
            free(str);
            continue ;
        }
        if (check_error_parsing(str))
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

	// signal(SIGINT, int_handler);
	// signal(SIGQUIT, quit_handler);
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
