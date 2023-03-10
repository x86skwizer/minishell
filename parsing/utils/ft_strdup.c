/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamrire <yamrire@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:12:27 by yamrire           #+#    #+#             */
/*   Updated: 2023/03/07 02:51:52 by yamrire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../merge.h"

char	*ft_strdup(const char *src)
{
	char			*ptr;
	unsigned int	num;

	num = 0;
	ptr = (char *) malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (src[num] != '\0')
	{
		ptr[num] = src[num];
		num++;
	}
	ptr[num] = '\0';
	return (ptr);
}
