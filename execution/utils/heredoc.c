/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:47:26 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/22 07:03:47 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

int	cmpstr(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	n;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	n = 0;
	if (len1 != len2)
		return (0);
	while (n < len1)
	{
		if (s1[n] != s2[n])
			return (0);
		n++;
	}
	return (1);
}

void	here_doc(t_pars *cmd)
{
	char	*here_doc;
	char	*limiter;

	limiter = ft_strjoin(cmd->delimiter, "\n");
	while (1)
	{
		write(1, "> ", 2);
		here_doc = get_next_line(0);
		if (here_doc == NULL)
		{
			free(limiter);
			break ;
		}
		if (cmpstr(limiter, here_doc))
		{
			free(here_doc);
			free(limiter);
			break ;
		}
		if (write(cmd->fd_input, here_doc, ft_strlen(here_doc)) == -1)
			handle_error(errno);
		free(here_doc);
	}
}
