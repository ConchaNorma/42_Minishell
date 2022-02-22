/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:22:05 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/22 19:52:25 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_unset(t_exec *vars, char **cmd)
{
	int		pos;
	char	**res;
	int		i;
	int		s;

	i = 0;
	s = 0;
	while(cmd[i])
	{
		if (s == 0 && !ft_memcmp(cmd[i], "unset", 6))
			s = 1;
		else if (s == 1)
		{
			pos = srch_var_in_envp(vars->envp, cmd[i]);
			if (pos == -1)
				return (-1);
			res = ft_del_str_from_arr(vars->envp, vars->envp[pos]);
			if (!res)
				return (-1);
			ft_frmtrx(vars->envp);
			vars->envp = res;
		}
		i++;
	}
	return (1);
}
