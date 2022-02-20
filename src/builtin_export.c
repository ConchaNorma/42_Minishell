/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:41:33 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 14:42:01 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int search_var_in_arr(char **arr, char *var_name)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(var_name);
	while (arr[i])
	{
		if (ft_strnstr(arr[i], var_name, len))
			return (i);
		i++;
	}
	return (-1);
}

static int find_repl_val_var_in_arr(char **arr, char *var)
{
	char *t_str;
	char *d_str;
	int cnt;

	t_str = ft_strchr(var, '=');
	if(!t_str)
		return (-1);
	cnt = t_str - var + 1;
	t_str = ft_substr(var, 0, cnt);
	if(!t_str)
		return (-1);
	cnt = search_var_in_arr(arr, t_str);
	if (cnt == -1)
		return (0);
	d_str = arr[cnt];
	arr[cnt] = ft_strdup(var);
	if(!arr[cnt])
	{
		arr[cnt] = d_str;
		cnt == -1;
	}
	else
		free(d_str);
	free(t_str);
	return (cnt);
}

int builtin_export(t_exec *vars, char *var)
{
	char **tmp;
	int res;

	res = find_repl_val_var_in_arr(vars->envp, var);
	if (!res)
	{
		tmp = ft_add_str_to_arr(vars->envp, var);	//дописать проверку на ошибку, возможно также проверка строки на корректность записи переменной
		ft_frmtrx(vars->envp);
		vars->envp = tmp;
		res = 0;
		while (vars->envp && vars->envp[res] && vars->envp[res + 1])
			res++;
	}
	return (res);
}
