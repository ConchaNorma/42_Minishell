/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:18:08 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:18:10 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	t;

	t = 0;
	while (t < n)
	{
		((unsigned char *)dst)[t] = ((unsigned char *)src)[t];
		if (((unsigned char *)src)[t++] == (unsigned char)c)
			return (dst + t);
	}
	return (NULL);
}
