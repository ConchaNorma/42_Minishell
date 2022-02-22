/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:41:33 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/22 19:20:20 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int find_repl_val_var_in_envp(char **envp, char *var)
{
	char	*var_name;
	char	*tmp;
	int		pos;

	var_name = get_varname(var, 0);
	if(!var_name)
		return (-1);
	pos = srch_var_in_envp(envp, var_name);
	if (pos == -1)
		return (0);
	tmp = envp[pos];
	envp[pos] = ft_strdup(var);
	if(!envp[pos])
	{
		envp[pos] = tmp;
		pos = -1;
	}
	else
		free(tmp);
	free(var_name);
	return (pos);
}

int builtin_export(t_exec *vars, char **cmd)
{
	char	**tmp;
	int		i;
	int		s;

	i = 0;
	s = 0;
	while(cmd[i])
	{
		if (s == 0 && !ft_memcmp(cmd[i], "export", 6))
			s = 1;
		else if (s == 1 && !find_repl_val_var_in_envp(vars->envp, cmd[i]))
		{
			tmp = ft_add_str_to_arr(vars->envp, cmd[i]);	//возможно нужна проверка строки на корректность записи переменной
			if (!tmp)
				return (-1);
			ft_frmtrx(vars->envp);
			vars->envp = tmp;
		}
		i++;
	}
	return (0);
}
