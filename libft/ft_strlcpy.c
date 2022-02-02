/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:20:49 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:20:51 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	if (!dst || !src)
		return (0);
	i = 0;
	k = ft_strlen((char *)src);
	if (dstsize == 0)
		return (k);
	while (i < dstsize - 1 && i < k)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (k);
}
