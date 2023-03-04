#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include "../parsing/parsing.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// ENV
typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

// PARSING
typedef	enum	e_file_type
{
	INPUT,
	OUTPUT,
	APPEND,
}				t_file_type;

typedef	struct e_file
{
	t_file_type	type;
	char		*path;
}				t_file;

typedef	struct s_cmd
{
	char		**args;
	t_file		*file;
}				t_cmd;

typedef	struct s_minishell
{
	t_list		*list_env;
	t_list		*cmd;
	t_env		*env;
	int			exit_code;
	// env linkedlist
}				t_minishell;

void	parsing_entry(char *line);

// EXECUTION
void	execution_entry();

// BUILTINS

// UTILS
void			memory_manager();
//liniked list
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void*));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));
//print
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
//search
int 			ft_strncmp(const char *s1, const char *s2, size_t n);
void			search_replace(char *key, char *value);
t_minishell*	get_minishell_data(t_minishell *minishell);
//env
void			env_fill(char **envp);
t_env			*env_create(char *key, char *value);

#endif