/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:13:04 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 03:51:00 by yamrire          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

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

typedef struct s_pars
{
	char	**cmd;
	char	**paths;
	char	*input;
	char	*output;
	char	*delimiter;
	int		fd_input;
	int		fd_output;
}	t_pars;

typedef struct s_data {
	int		ipip;
	int		i;
	t_list	*curr;
	t_pars	*cmd;
}	t_data;

typedef struct s_merge {
	t_list	*env;
	pid_t	*pid;
	int		fd_pip[2];
	int		fd_tmp;
	int		fd_tmpin;
	int		fd_tmpout;
	int		nbr_cmd;
	int		exit_code;
}	t_merge;

extern t_merge	g_global;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
char	**arrange_paths(void);
char	**get_paths(void);
void	free_double(char **pointer);
void	search_replace(char *key, char *value);
t_env	*env_create(char *key, char *value);
void	add_cmd_path(t_pars **cmd);
void	handle_error(int static_code);
int		split_arg(char *str, t_pars **cmd);
int		count_arg(char *str);
int		check_error_parsing(char *str);
int		count_cmd(char *str);
int		fill_cmd_list(char *str, t_list **list);
int		check_expansion(char *cmd);
int		check_env_var(char *s);
void	expand(char **s);
void	expand_arg(char **arg);
void	exit_error(int static_code, char *cmd);
void	env_fill(char **envp);
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_export(char **argv);
int		builtin_unset( char **args);
int		builtin_exit(char **args);
void	rl_replace_line(const char *test, int flag);
void	execute(t_list *list, char **env);
char	*get_next_line(int fd);
void	here_doc(t_pars *cmd);
char	*parent_process(t_list *list);
void	check_entry(t_pars *cmd);
void	pipline(void);
void	dup_tmp(void);
void	check_position(t_pars *cmd, int i);
void	end_program(t_pars *cmd);
void	check_entry(t_pars *cmd);
void	init_pipe(void);
void	pipline(void);
void	dup_tmp(void);
void	check_position(t_pars *cmd, int i);
void	int_handler(int sig);
void	quit_handler(int sig);
char	*ft_trim(char *s, char c);

#endif