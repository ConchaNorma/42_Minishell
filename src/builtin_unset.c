/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:22:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 20:39:25 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_unset(t_exec *vars, char *var)
{
	int		pos;
	char	**res;

	pos = srch_var_in_envp(vars->envp, var);
	if (pos == -1)
		return (-1);
	res = ft_del_str_from_arr(vars->envp, vars->envp[pos]);
	if (!res)
		return (-1);
	ft_frmtrx(vars->envp);
	vars->envp = res;
	return (pos);
}
