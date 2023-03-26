/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:00:07 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 20:01:47 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

int	override_env_vat(t_list	*env_list, char	**list, char *argv)
{
	t_env	*env_tmp;
	int		check;

	check = 0;
	while (env_list)
	{
		env_tmp = (t_env *)(env_list->content);
		if (ft_strcmp(env_tmp->key, list[0]) == 0)
		{
			if (list[1])
			{
				free(env_tmp->value);
				env_tmp->value = ft_strdup(list[1]);
			}
			else if (ft_strchr(argv, '=') && !list[1])
			{
				free(env_tmp->value);
				env_tmp->value = ft_strdup("");
			}
			check = 1;
		}
		env_list = env_list->next;
	}
	return (check);
}

void	add_env_var(char **list, char *argv)
{
	t_env	*env_node;

	if (list[1] == NULL && ft_strchr(argv, '='))
		env_node = env_create(list[0], "");
	else if (list[1] == NULL && !ft_strchr(argv, '='))
		env_node = env_create(list[0], NULL);
	else
		env_node = env_create(list[0], list[1]);
	ft_lstadd_back(&(g_global.env), ft_lstnew(env_node));
}

void	check_quotes(char **argv, int j)
{
	if (ft_strchr(argv[j], '\"'))
		argv[j] = ft_trim(argv[j], '\"');
	if (ft_strchr(argv[j], '\''))
		argv[j] = ft_trim(argv[j], '\'');
}
