#include "../../merge.h"

void	ft_lstswap(t_list *lst1, t_list *lst2)
{
	t_env	*swapper;

	swapper = lst1->content;
	lst1->content = lst2->content;
	lst2->content = swapper;
}

t_list	*sort_env(t_list *env_list)
{
	t_list	*tmp;
	t_list	*tmp1;
	t_env	*env_tmp;
	t_env	*env_tmp2;

	tmp = env_list;
	while (tmp)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			env_tmp = (t_env *)(tmp->content);
			env_tmp2 = (t_env *)(tmp1->content);
			if (ft_strcmp(env_tmp->key, env_tmp2->key) > 0)
			{
				ft_lstswap(tmp1, tmp);
				env_tmp = (t_env *)(tmp->content);
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
	tmp = env_list;
	return (tmp);
}

int	print_export(t_list *env_list)
{
	t_env		*env_tmp;
	t_list		*env_list1;

	env_list1 = sort_env(env_list);

	env_list1 = g_global.env;
	while (env_list1)
	{
		env_tmp = (t_env *)(env_list1->content);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_tmp->key, STDOUT_FILENO);
		if (env_tmp->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_tmp->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd("", STDOUT_FILENO);
		env_list1 = env_list1->next;
	}
	return (0);
}

int	builtin_export(char **argv)
{
	int			j;
	t_list		*env_list;
	t_env		*env_tmp;
	int			check;
	char		**list;
	t_env	*env_node;

	j = 0;
	check = 0;
	env_list = g_global.env;
	if (argv[1] == NULL)
		print_export(env_list);
	else
	{
		j = 1;
		while (argv[j])
		{
			list = ft_split(argv[j], '=');
			check = 0;
			while (env_list)
			{
				env_tmp = (t_env *)(env_list->content);
				if (ft_strcmp(env_tmp->key, list[0]) == 0)
				{
					env_tmp->value = list[1];
					check = 1;
				}
				env_list = env_list->next;
			}
			
			env_list = g_global.env;
			if (check == 0)
			{
				env_node = env_create(list[0], list[1]);
				ft_lstadd_back(&(g_global.env), ft_lstnew(env_node));
			}
			j++;
		}
	}
	return (0);
}

