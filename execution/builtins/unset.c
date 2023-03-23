#include "../../merge.h"

void	tenv_free(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	//adding protection if the key or value is NULL
	free(env->key);
	free(env->value);
	free(env);
}


int	builtin_unset( char **args)
{
	t_list	*tmp;
	t_env	*env_tmp;
	int		i;

	i = 1;
	tmp = g_global.env;
	while (tmp)
	{
		env_tmp = tmp->content;
		ft_putstr_fd(env_tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(env_tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	while (args[i])
	{
		tmp = g_global.env;
		while (tmp)
		{
			env_tmp = (t_env *)(tmp->content);
			if (ft_strncmp(env_tmp->key, args[i], ft_strlen(env_tmp->key)) == 0)
			{
				ft_lstdelone(tmp, tenv_free);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	tmp = g_global.env;
	printf("-----------after unset------------\n");
	while (tmp)
	{
		env_tmp = tmp->content;
		ft_putstr_fd(env_tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(env_tmp->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
