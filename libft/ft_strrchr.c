/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:22:18 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:22:19 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int				i;
	unsigned char	*tmp;

	tmp = (unsigned char *)str;
	i = ft_strlen((char *)str);
	while (i >= 0)
	{
		if (tmp[i] == (unsigned char)ch)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}
