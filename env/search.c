#include "../execution/minishell.h"

void	search_replace(char *key, char *value)
{
	t_list		*tmp;
	t_env		*tmp_content;
	t_minishell	*minishell;

	minishell = get_minishell_data(NULL);
	tmp = minishell->list_env;
	tmp_content = tmp->content;
	while (tmp)
	{
		if (ft_strcmp(tmp_content->key, key) == 0)
		{
			tmp_content->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}
