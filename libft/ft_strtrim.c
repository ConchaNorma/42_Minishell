/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:22:12 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:22:14 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	k = ft_strlen((char *)s1);
	while (i < k)
	{
		if (NULL == ft_strchr(set, (char)s1[i]))
			break ;
		i++;
	}
	while (k > 0)
	{
		if (NULL == ft_strchr(set, (char)s1[k]))
			break ;
		k--;
	}
	return (ft_substr(s1, (unsigned int)i, k - i + 1));
}
