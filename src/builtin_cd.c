/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:09:20 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/28 22:42:29 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void chng_oldpwd(char **path, t_exec *vars)
{
	int		i;
	char	*tmp;

	i = srch_var_in_envp(vars->envp, "PWD");
	tmp = NULL;
	if (i != -1)
	{
		tmp = ft_strjoin("OLDPWD=", get_varvalue(vars->envp[i]));
		find_repl_val_var_in_envp(vars->envp, tmp);
		free(tmp);
		tmp = ft_strjoin("PWD=", *path);
		find_repl_val_var_in_envp(vars->envp, tmp);
		free(tmp);
	}
	free(*path);
}

static int ft_cd_hyphen(char **path, t_exec *vars, int pos)
{
	char	*tmp;

	if (pos == -1)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		if (!vars->pid)
		{
			free(*path);
			ft_errfrex(vars, FREX, 1, NULL);
		}
		vars->exit_status = 1;
		return (1);
	}
	tmp = ft_strdup(get_varvalue(vars->envp[pos]));
	if (chdir(tmp))
	{
		free(*path);
		return (-1);
	}
	ft_putendl_fd(tmp, 1);
	chng_oldpwd(&tmp, vars);
	return (1);
}

static char *ft_cd_wavy_line(char **path, t_exec *vars)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (vars->envp[i])
	{
		tmp = ft_strnstr(vars->envp[i], "HOME=", 5);
		if (tmp)
		{
			free(*path);
			return(ft_strdup(tmp + 5));
		}
		i++;
	}
	return (*path);
}

int builtin_cd(char	*dir, t_exec *vars)
{
	char	*path;
	int		pos;

	path = getcwd(NULL, 0);
	if (!path)
		return (-1);
	pos = srch_var_in_envp(vars->envp, "OLDPWD");
	if (dir && ft_strlen(dir) == 1 && dir[0] == '-')
		return (ft_cd_hyphen(&path, vars, pos));
	if (!dir || dir[0] == '~')
		path = ft_cd_wavy_line(&path, vars);
	if (dir)
		path = ft_cd_getpath(dir, &path);
	if (chdir(path))
	{
		free(path);
		return (-1);
	}
	chng_oldpwd(&path, vars);
	return (1);
}
