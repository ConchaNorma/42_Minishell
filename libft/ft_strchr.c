/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:19:57 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:19:58 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	size_t	i;
	size_t	t;

	i = ft_strlen((char *)str);
	t = 0;
	while (t <= i)
	{
		if (str[t] == (char)ch)
			return ((char *)(str + t));
		t++;
	}
	return (NULL);
}
