#include "../execution/minishell.h"
#include "../parsing/parsing.h"
#include "../merge.h"

t_env	*env_create(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	return (env);
}

void	env_fill(char **envp)
{
	t_env	*env_node;
	char	**pointer;
	int		i;

	i = 0;
	while (envp[i])
	{
		pointer = ft_split(envp[i], '=');
		env_node = env_create(pointer[0], pointer[1]);
		ft_lstadd_back(&my_global->env, ft_lstnew(env_node));
		i++;
	}
}