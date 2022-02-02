/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:18:32 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:18:33 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	t;

	t = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (t < n)
	{
		((unsigned char *)dst)[t] = ((unsigned char *)src)[t];
		t++;
	}
	return (dst);
}
