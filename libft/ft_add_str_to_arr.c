/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_to_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:21:45 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 18:10:38 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_str_to_arr(char **arr, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	while (arr && arr[i])
		i++;
	if (str)
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i--] = NULL;
	if (str)
	{
		tmp[i--] = ft_strdup(str);
		if (!tmp[i + 1])
		{
			free(tmp);
			return (NULL);
		}
	}
	return (ft_arrcpy_strdup(arr, tmp));
}
