/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:22:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 14:45:43 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**del_str_from_arr(char **arr, char *str)
{
	int i;
	int len;
	int len_s;
	char **tmp;

	i = 0;
	len_s = ft_strlen(str);
	//считаем длину массива arr
	len = 0;
	while (arr[len])
		len++;

	//проверяем, есть ли в массиве arr строка str
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == len_s && ft_strnstr(arr[i], str, len_s))
			break ;
		i++;
	}
	if (len == i)
		return (NULL);

	//выделяем память под временный массив tmp длинной N-1 (N - длина масива arr)
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (NULL);
	tmp[len-1] = NULL;

	//копируем строки массива arr в массив tmp
	i = 0;
	len = 0;
	while (arr[i])
	{
		if (ft_strlen(arr[i]) == len_s && ft_strnstr(arr[i], str, len_s))
			len = 1;
		else
		{
			tmp[i-len] = ft_strdup(arr[i]);
			if(!tmp[i-len])
			{
				ft_frmtrx(tmp);
				return (NULL);
			}
		}
		i++;
	}
	return (tmp);
}

//если запустить в баше ______gert unset cat test.c  ______gretta
//где ______gert ______gretta предварительно экспортированные переменные
//баш выдаст bash: ______gert: command not found
//что говорит, работа с переменными начинается только после проверки работы

int	builtin_unset(t_exec *vars, char *var)
{
	return (0);
}
