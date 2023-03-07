#ifndef _MINISHELL_H_
#define _MINISHELL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include "../merge.h"

int			ft_lstsize(t_list *lst);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int 		ft_strncmp(const char *s1, const char *s2, size_t n);
void		search_replace(char *key, char *value);
t_env		*env_create(char *key, char *value);

#endif