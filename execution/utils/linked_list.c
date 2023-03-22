#include "../../merge.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst)
	{
		if (*alst)
			new->next = *alst;
		*alst = new;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (!f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
// {
// 	t_list	*first;
// 	t_list	*new;

// 	if (!f || !del)
// 		return (NULL);
// 	first = NULL;
// 	while (lst)
// 	{
// 		if (!(new == ft_lstnew((*f)(lst->content))))
// 		{
// 			while (first)
// 			{
// 				new = first->next;
// 				(*del)(first->content);
// 				free(first);
// 				first = new;
// 			}
// 			lst = NULL;
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&first, new);
// 		lst = lst->next;
// 	}
// 	return (first);
// }

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
