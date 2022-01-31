/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:21:40 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:21:42 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (big[i] != 0 && i < len)
	{
		k = 0;
		while (big[i + k] == little[k] && little[k] != 0 && k + i < len)
			k++;
		if (k == ft_strlen((char *)little))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
