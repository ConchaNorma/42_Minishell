/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:41:33 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/04 00:59:03 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	concat_varvalue(t_exec *vars, char *cmd, char *adrs)
{
	char	*tmp[3];
	int		i;

	tmp[0] = ft_substr(cmd, 0, (adrs - cmd - 1));
	i = srch_var_in_envp(vars->envp, tmp[0]);
	if (i == -1)
	{
		tmp[2] = ft_strjoin(tmp[0], adrs);
		i = add_var_in_envp(vars, tmp[2]);
	}
	else
	{
		tmp[2] = ft_strjoin(get_varvalue(vars->envp[i]), (adrs + 1));
		tmp[1] = ft_strjoin("=", tmp[2]);
		free(tmp[2]);
		tmp[2] = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[1]);
		find_repl_val_var_in_envp(vars->envp, tmp[2]);
		i = 0;
	}
	free(tmp[0]);
	free(tmp[2]);
	return (i);
}

static int	add_chng_var(t_exec *vars, char *cmd)
{
	char	*adrs;
	int		res;

	res = find_repl_val_var_in_envp(vars->envp, cmd);
	if (res == -1)
	{
		adrs = ft_strchr(cmd, '=');
		if (*(adrs - 1) == '+')
			return (concat_varvalue(vars, cmd, adrs));
		else if (add_var_in_envp(vars, cmd))
			return (1);
	}
	return (0);
}

static int	chk_spc_sym(char *cmd)
{
	char	*pl;
	char	*eq;

	eq = ft_strchr(cmd, '=');
	pl = ft_strchr(cmd, '+');
	if (cmd[0] == '=' || ft_isdigit(cmd[0]) || (eq && pl && (eq - pl) > 1))
		return (1);
	return (0);
}

static void	put_var_envp_declare(char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		tmp = get_varname(envp[i], 1);
		ft_putstr_fd(tmp, 1);
		free(tmp);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(get_varvalue(envp[i]), 1);
		ft_putendl_fd("\"", 1);
		i++;
	}
}

int	builtin_export(t_exec *vars, char **cmd)
{
	int	i;
	int	s;

	i = -1;
	s = 0;
	while (cmd[++i])
	{
		if (s == 0 && !ft_memcmp(cmd[i], "export", 6))
		{
			if (!cmd[i + 1])
				put_var_envp_declare(vars->envp);
			s = 1;
		}
		else if (s == 1 && chk_spc_sym(cmd[i]))
			err_valid_id(vars, cmd[i]);
		else if (s == 1 && ft_strchr(cmd[i], '=') && add_chng_var(vars, cmd[i]))
			return (1);
	}
	return (1);
}
