/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:26:49 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/26 16:55:53 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../merge.h"

int	double_quotes(t_pars **cmd, char *str, int i, int j)
{
	int	start;

	i++;
	start = i;
	while (str[i] && str[i] != 34)
		i++;
	(*cmd)->cmd[j] = ft_substr(str, start, i - start);
	while (check_expansion((*cmd)->cmd[j]))
		expand_arg((&(*cmd)->cmd[j]));
	i++;
	return (i);
}

int	single_quotes(t_pars **cmd, char *str, int i, int j)
{
	int	start;

	i++;
	start = i;
	while (str[i] && str[i] != 39)
		i++;
	(*cmd)->cmd[j] = ft_substr(str, start, i - start);
	i++;
	return (i);
}

int	append_file(t_pars **cmd, char *str, int i)
{
	int	start;

	i++;
	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	if ((*cmd)->output)
	{
		close((*cmd)->fd_output);
		free((*cmd)->output);
	}
	(*cmd)->output = ft_substr(str, start, i - start);
	(*cmd)->fd_output = open((*cmd)->output, O_APPEND
			| O_CREAT | O_RDWR, 0644);
	if ((*cmd)->fd_output == -1)
		handle_error(errno);
	return (i);
}

int	output_file(t_pars **cmd, char *str, int i)
{
	int	start;

	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	if ((*cmd)->output)
	{
		close((*cmd)->fd_output);
		free((*cmd)->output);
	}
	(*cmd)->output = ft_substr(str, start, i - start);
	(*cmd)->fd_output = open((*cmd)->output, O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if ((*cmd)->fd_output == -1)
		handle_error(errno);
	return (i);
}

int	heredoc_open(t_pars **cmd, char *str, int i)
{
	int	start;

	i++;
	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	if ((*cmd)->delimiter || ((*cmd)->input))
	{
		close((*cmd)->fd_input);
		if ((*cmd)->delimiter)
			free((*cmd)->delimiter);
		if ((*cmd)->input)
			free((*cmd)->input);
	}
	(*cmd)->delimiter = ft_substr(str, start, i - start);
	(*cmd)->fd_input = open("/tmp/.here_doc", O_APPEND
			| O_CREAT | O_RDWR | O_TRUNC, 0644);
	here_doc(*cmd);
	close((*cmd)->fd_input);
	(*cmd)->fd_input = open("/tmp/.here_doc", O_RDONLY);
	return (i);
}
