/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:08:42 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/22 01:47:44 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	**cmd;
	int	i;

	if (ac >= 1)
	{
		av[1] = NULL;
		while (1)
		{
			str = readline("minishell$  ");
			if (str && *str)
				add_history(str);

			// Parsing
			cmd = get_cmd_options(str, env);
			i = 0;
			while (cmd[i])
				printf("%s\n", cmd[i++]);
			free_double(cmd);
			free(str);
		}
	}
	return (0);
}