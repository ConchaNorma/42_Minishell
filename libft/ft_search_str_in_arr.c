/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_str_in_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:46:04 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 17:07:33 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_search_str_in_arr(char **arr, char *str)
{
	int		i;
	size_t	len;

	if (!str || !arr)
		return (-1);
	i = 0;
	len = ft_strlen(str);
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == len && ft_strnstr(arr[i], str, len))
			return (i);
		i++;
	}
	return (-1);
}
