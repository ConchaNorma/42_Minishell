/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:18:43 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:18:44 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	t;

	t = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if ((unsigned char *) &dst[0] > (unsigned char *) &src[0])
	{
		while (len-- > 0)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		return (dst);
	}
	while (t < len)
	{
		((unsigned char *)dst)[t] = ((unsigned char *)src)[t];
		t++;
	}
	return (dst);
}
