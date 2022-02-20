/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_str_from_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:52:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 19:31:38 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**arrcpy_without_str(char **arr, char **res, int pos)
{
	int		len;
	int		start;
	char	**tmp;

	len = ft_arrlen((void **)arr);
	start = 0;
	if (pos)
	{
		tmp = ft_subarr_strdup(arr, res, start, pos);
		if (!tmp)
			return (NULL);
	}
	start = pos + 1;
	if (start < len)
	{
		tmp = ft_subarr_strdup(arr, (res + pos), start, (len - 1 - pos));
		if (!tmp)
		{
			ft_frmtrx(res);
			return (NULL);
		}
	}
	return (res);
}

char	**ft_del_str_from_arr(char **arr, char *str)
{
	int		pos;
	int		len;
	char	**res;

	len = ft_arrlen((void **)arr);
	pos = ft_search_str_in_arr(arr, str);
	if (pos == -1)
		return (NULL);
	res = malloc(sizeof(char *) * len);
	if (!res)
		return (NULL);
	res[len - 1] = NULL;
	return (arrcpy_without_str(arr, res, pos));
}
