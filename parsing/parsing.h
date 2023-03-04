/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:09:09 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/04 05:07:17 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_listp {
	t_pars *cmd;
	struct s_listp *next;
}	t_listp;

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
t_listp	*ft_lstlast_cmd(t_listp *lst);
void	ft_lstaddback_cmd(t_listp **lst, t_listp *new);
t_listp	*ft_lstnew_cmd(t_pars *cmd);
void	add_cmd_path(t_pars **cmd);
void	handle_error(int static_code);
int		split_arg(char *str, t_pars **cmd);
int		count_arg(char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		check_error_parsing(char *str);
int		count_cmd(char *str);
int		fill_cmd_list(char **env, char *str, t_listp **list);

#endif