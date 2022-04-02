/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:25:15 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/29 20:26:00 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_echo(char *cmd)
{
	int	j;

	j = 0;
	if (cmd[0] != '-')
		return (-1);
	if (cmd[j] == '-')
	{
		while (cmd[++j])
		{
			if (cmd[j] != 'n')
				return (-1);
		}
	}
	return (0);
}

int	builtin_echo(char **cmd)
{
	int	i;
	int	nl;
	int	flag;

	i = 0;
	nl = 0;
	flag = 0;
	while (cmd[++i])
	{
		if (nl != -1)
			nl = ft_echo(cmd[i]);
		if (nl == -1)
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			if (cmd[i + 1])
				write(1, " ", 1);
		}
		if (nl == 0)
			flag = 1;
	}
	if (flag != 1)
		write(1, "\n", 1);
	return (1);
}
