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


int    builtin_unset( char **args)
{
    t_list    *tmp;
    t_env    *env_tmp;
    int        i;

    i = 1;
    tmp = g_global.env;
    while (args[i])
    {
        tmp = g_global.env;
        t_list *parent = NULL;
        while (tmp)
        {
            env_tmp = (t_env *)(tmp->content);
            if (ft_strcmp(env_tmp->key, args[i]) == 0)
            {
                if (parent)
                    parent->next = tmp->next;
                else
                    g_global.env = tmp->next;
                ft_lstdelone(tmp, tenv_free);
                break ;
            }
            parent = tmp;
            tmp = tmp->next;
        }
        i++;
    }
    tmp = g_global.env;
    return (0);
}