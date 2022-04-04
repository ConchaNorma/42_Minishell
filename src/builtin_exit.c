/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:47:48 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/04 00:50:18 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_check_atollm(const char *str)
{
	unsigned long long	r;
	int					s;

	if (ft_strlen(str) > 20)
		return (1);
	r = 0;
	s = 0;
	while (*str)
	{
		if (*str == '-')
		{
			s++;
			str++;
			continue ;
		}
		r = (r * 10) + ((unsigned long long)*str - 48);
		str++;
	}
	if (s)
		r -= 1;
	return (r > 9223372036854775807);
}

static int	exstat_hand(char **code, int res, int ex_st)
{
	char	*tmp;
	char	*tmp2;

	if (code[1] && !res)
		ex_st = ft_atoi(code[1]);
	if (!res)
		ex_st = (int)(unsigned char)ex_st;
	if (code[1] && code[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (res || (code[1] && ft_check_atollm(code[1])))
	{
		tmp = ft_strjoin("minishell: exit: ", code[1]);
		tmp2 = ft_strjoin(tmp, ": numeric argument required");
		ft_putendl_fd(tmp2, 2);
		free(tmp);
		free(tmp2);
		ex_st = 255;
	}
	return (ex_st);
}

void	builtin_exit(t_exec *vars, char **code)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (vars->st == 1)
		ft_putendl_fd("exit", 2);
	while (code[1] && code[1][i])
	{
		if (!i && code[1][i] == '-')
		{
			if (!code[1][i + 1])
			{
				res = 1;
				break ;
			}
			i++;
			continue ;
		}
		if (!ft_isdigit(code[1][i++]))
			res = 1;
	}
	res = exstat_hand(code, res, vars->exit_status);
	clean_base_struct(vars, 1);
	exit(res);
}
