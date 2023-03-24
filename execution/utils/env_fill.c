#include "../../merge.h"

t_env	*env_create(char *key, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	return (env);
}

void	env_fill(char **envp)
{
	char	**pointer;
	int		i;

	i = 0;
	g_global.env = NULL;
	while (envp[i])
	{
		pointer = ft_split(envp[i], '=');
		ft_lstadd_back(&(g_global.env), ft_lstnew(env_create(pointer[0], pointer[1])));
		free_double(pointer);
		i++;
	}
}
