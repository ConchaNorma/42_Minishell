/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:33:13 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/19 12:40:59 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char **arr_copy_or_free_to(char **from, char **to)
{
	int i;

	i = 0;
	while (from && from[i])
	{
		to[i] = ft_strdup(from[i]);
		if (!to[i])
		{
			ft_frmtrx(to);
			free(to);
			return (NULL);
		}
		i++;
	}
	return (to);
}

char	**arr_add_one_str(char **arr, char *str)
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
		if (!tmp[i+1])
		{
			free(tmp);
			return (NULL);
		}
	}
	return (arr_copy_or_free_to(arr, tmp));
}
/*
char	**del_str_from_arr_unset(char **arr, char *str)
{

}
*/
