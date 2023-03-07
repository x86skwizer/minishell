/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:13:04 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/07 03:27:35 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_H
# define MERGE_H

//# include "./execution/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_data {
	int		nbr;
	int		ipip;
	int		i;
}	t_data;

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

typedef	struct s_merge
{
	t_list		*env;
	int			exit_code;
}				t_merge;

extern t_merge	*my_global;

void	env_fill(char **envp);
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
t_list	*ft_lstnew(void *content);
void	add_cmd_path(t_pars **cmd);
void	handle_error(int static_code);
int		split_arg(char *str, t_pars **cmd);
int		count_arg(char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		check_error_parsing(char *str);
int		count_cmd(char *str);
int		fill_cmd_list(char **env, char *str, t_list **list);

//builtins
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(void);

#endif