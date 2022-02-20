/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subarr_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:45:30 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 18:15:09 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_subarr_strdup(char **from, char **to, int start, size_t len)
{
	size_t	i;
	size_t	l;

	if (!from || start < 0 || (size_t) start >= ft_arrlen((void **)from))
		return (NULL);
	l = ft_arrlen((void **)(from + start));
	if (l > len)
		l = len;
	i = 0;
	while (i < l)
	{
		to[i] = ft_strdup(from[start]);
		if (!to[i])
		{
			ft_frmtrx(to);
			free(to);
			return (NULL);
		}
		i++;
		start++;
	}
	return (to);
}
