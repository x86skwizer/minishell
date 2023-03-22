#include "../../merge.h"

void	search_replace(char *key, char *value)
{
	t_env	*tmp_content;
	t_list	*tmp;

	tmp = g_global->env;
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
