/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:23:57 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/04 01:11:53 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_repl_val_var_in_envp(char **envp, char *var)
{
	char	*var_name;
	char	*tmp;
	int		pos;

	var_name = get_varname(var, 0);
	if (!var_name)
		return (-1);
	pos = srch_var_in_envp(envp, var_name);
	if (pos == -1)
		return (-1);
	tmp = envp[pos];
	envp[pos] = ft_strdup(var);
	if (!envp[pos])
	{
		envp[pos] = tmp;
		pos = -1;
	}
	else
		free(tmp);
	free(var_name);
	return (pos);
}

int	srch_var_in_envp(char **envp, char *var_name)
{
	char	*tmp;
	int		i;

	tmp = ft_strjoin(var_name, "=");
	if (!tmp)
		return (-1);
	i = ft_str_in_arrstr(envp, tmp, ft_strlen(tmp));
	free(tmp);
	return (i);
}

int	add_var_in_envp(t_exec *vars, char *var)
{
	char	**tmp;

	tmp = ft_add_str_to_arr(vars->envp, var);
	if (!tmp)
		return (1);
	ft_frmtrx(vars->envp);
	vars->envp = tmp;
	return (0);
}
