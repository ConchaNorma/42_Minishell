/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/10 22:48:00 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int builtin_exec(t_exec *vars);

int builtin_check(t_exec *vars)
{
	int len_cmd;

	len_cmd = ft_strlen(vars->exe[0]);
	if (len_cmd == 6 && !ft_memcmp(vars->exe[0], "export", len_cmd))
		;
	else if (len_cmd == 5 && !ft_memcmp(vars->exe[0], "unset", len_cmd))
		;
	else if (len_cmd == 4)
	{
		if (!ft_memcmp(vars->exe[0], "echo", len_cmd))
			;
		if (!ft_memcmp(vars->exe[0], "exit", len_cmd))
			;
	}
	else if (len_cmd == 3)
	{
		if (!ft_memcmp(vars->exe[0], "env", len_cmd))
			;
		if (!ft_memcmp(vars->exe[0], "pwd", len_cmd))
			;
	}
	else if (len_cmd == 2 && !ft_memcmp(vars->exe[0], "cd", len_cmd))
		;
	return (0);
}

