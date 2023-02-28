/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:09:09 by yamrire           #+#    #+#             */
/*   Updated: 2023/02/28 03:04:00 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/errno.h>

typedef struct s_cmd
{
	char	**cmd;
	char	**paths;
	char	*input;
	char	*output;
	char	*append;
	pid_t	pid;
}	t_cmd;


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
void	add_cmd_path(t_cmd **cmd);
void	handle_error(int static_code);
void	split_arg(char *str, t_cmd **cmd);
int		count_arg(char *str);

#endif