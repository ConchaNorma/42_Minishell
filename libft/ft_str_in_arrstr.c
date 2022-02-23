/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_in_arrstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:58:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/23 17:32:30 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_in_arrstr(char **arr, char *str, size_t len_s)
{
	int		i;
	size_t	l_s;
	size_t	l_as;

	if (!str)
		return (-1);
	i = 0;
	l_s = ft_strlen(str);
	if (len_s < l_s)
		return (-1);
	while (arr[i])
	{
		l_as = ft_strlen(arr[i]);
		if (l_as < l_s)
			continue ;
		if (l_as > len_s)
			l_as = len_s;
		if (ft_strnstr(arr[i], str, l_as))
			return (i);
		i++;
	}
	return (-1);
}
