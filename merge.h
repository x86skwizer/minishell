/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 05:13:04 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/04 11:12:51 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_H
# define MERGE_H

# include "./parsing/parsing.h"
# include "./execution/minishell.h"

typedef struct s_data {
	int		nbr;
	int		ipip;
	int		i;
}	t_data;

typedef	struct s_merge
{
	t_list		*env;
	int			exit_code;
}				t_merge;

extern t_merge	*my_global;

#endif