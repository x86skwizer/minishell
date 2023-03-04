// Commun Functions in parsing/parsing.h

void	free_double(char **pointer);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);

// Commun Functions in execution/minishell.h

t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

// To Include Both Headers From execution/ Folder

How can i get access to key variable in the struct t_env from t_merge using variable curr in main in this c language script:

typedef	struct s_merge
{
	t_list		*env;
	int			exit_code;
}				t_merge;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

extern t_merge	*my_global;

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

int main(int ac, char **av, char **env)
{
	t_list	*curr;


	curr = my_global->env;
	my_global = malloc(sizeof(t_merge));
}