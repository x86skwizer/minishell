/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:09:09 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/02 05:53:28 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/errno.h>

typedef struct s_pars
{
	char			**cmd;
	char			**paths;
	char			*input;
	char			*output;
	char			*append;
	char			*delimiter;
	pid_t			pid;
}	t_pars;

typedef struct s_list {
	t_pars *cmd;
	struct s_list *next;
}	t_list;

char	**arrange_paths(char **envp);
char	**get_paths(char **envp);
void	free_double(char **pointer);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(t_pars *cmd);
void	add_cmd_path(t_pars **cmd);
void	handle_error(int static_code);
int		split_arg(char *str, t_pars **cmd);
int		count_arg(char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		check_error_parsing(char *str);
int		count_cmd(char *str);
int		fill_cmd_list(char **env, char *str, t_list **list);

//bultins
int	builtin_echo(char **args);

#endif