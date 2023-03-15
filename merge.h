/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:13:04 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/14 08:28:21 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_H
# define MERGE_H

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
	char	*key;
	char	*value;
}					t_env;

typedef struct s_data {
	int	ipip;
	int	i;
}	t_data;

typedef struct s_pars
{
	char	**cmd;
	char	**paths;
	char	*input;
	char	*output;
	char	*append;
	char	*delimiter;
	int		fd_input;
	int		fd_output;
	int		fd_append;	
}	t_pars;

typedef	struct s_merge
{
	t_list	*env;
	pid_t	*pid;
	int		fd_pip[2];
	int		fd_tmp;
	int		nbr_cmd;
	int		exit_code;
}	t_merge;

extern t_merge	*my_global;

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
int		check_expansion(char *cmd);
int		check_env_var(char *s);
void	expand(char **s);
void	expand_arg(char **arg);
// env
void	env_fill(char **envp);

// builtins
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(void);
void	builtin_env(void);

//execution
void	execute(t_list *list, char **env);

#endif