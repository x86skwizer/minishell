#include "../minishell.h"

int builtin_export(char **argv)
{
	int			j;
	t_list		*env_list_;
	t_minishell	*minishell;
	t_env		*env_tmp;
	int			check;
	char		**list;

	j = 0;
	check = 0;
	minishell = get_minishell_data(NULL);
	env_list_ = minishell->list_env;
	if (argv[1] == NULL)
	{
		while (env_list_)
		{
			env_tmp = (t_env *)(env_list_->content);
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(env_tmp->key, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_tmp->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
			env_list_ = env_list_->next;
		}
		return (0);
	}
	else
	{
		j = 1;
		while (argv[j])
		{
			printf("argv[%d]: %s\n", j, argv[j]);
			list = ft_split(argv[j], '=');
			while (env_list_)
			{
				env_tmp = (t_env *)(env_list_->content);
				if (ft_strncmp(env_tmp->key, list[0], ft_strlen(list[0])) == 0)
				{
					env_tmp->value = list[1];
					check = 1;
				}
				env_list_ = env_list_->next;
			}
			env_list_ = minishell->list_env;
			if (check == 0)
				ft_lstadd_back(&minishell->list_env, ft_lstnew(env_create(list[0], list[1])));
			j++;
		}
	}
	return (0);
}
