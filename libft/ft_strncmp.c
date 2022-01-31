/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:21:16 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:21:18 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	k;

	k = 0;
	while (k < n && str1[k] && str2[k])
	{
		if (str1[k] != str2[k])
			return ((unsigned char)str1[k] - (unsigned char)str2[k]);
		k++;
	}
	if (k < n)
		return ((unsigned char)str1[k] - (unsigned char)str2[k]);
	return (0);
}
