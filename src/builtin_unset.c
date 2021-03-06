/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:22:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/29 20:58:20 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_unset(t_exec *vars, char **cmd)
{
	int		pos;
	char	**res;
	int		i;

	i = 1;
	while (cmd[i])
	{
		pos = srch_var_in_envp(vars->envp, cmd[i]);
		if (pos == -1)
			return (1);
		res = ft_del_str_from_arr(vars->envp, vars->envp[pos]);
		if (!res)
			return (1);
		ft_frmtrx(vars->envp);
		vars->envp = res;
		i++;
	}
	return (1);
}
