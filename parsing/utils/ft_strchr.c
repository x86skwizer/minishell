/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:07:30 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/01 00:19:11 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*ft_strchr(const char *str, int c)
{
	char	alpha;
	int		num;
	char	*s;

	s = (char *)str;
	alpha = (char) c;
	if (!s)
		return (NULL);
	num = 0;
	while (s[num] != '\0')
	{
		if (s[num] == alpha)
			return (&s[num]);
		num++;
	}
	if (c == '\0')
		return (&s[num]);
	return (NULL);
}