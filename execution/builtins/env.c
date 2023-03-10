#include "../minishell.h"
#include "../../merge.h"

void	builtin_env(void)
{
	t_list		*tmp;
	t_env		*tmp_content;

	tmp = my_global->env;
	while (tmp)
	{
		tmp_content = (t_env *)tmp->content;
		ft_putstr_fd(tmp_content->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(tmp_content->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	free(tmp);
}
