/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:09:20 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/03 17:25:39 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	err_search_var(char **path, t_exec *vars, char *str)
{
	char *tmp1;
	char *tmp2;

	tmp1 = ft_strjoin("minishell: cd: ", str);
	tmp2 = ft_strjoin(tmp1, " not set");
	ft_putendl_fd(tmp2, 2);
	free(tmp1);
	free(*path);
	vars->exit_status = 1;
}

static void	chng_oldpwd(char **path, t_exec *vars)
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

static int	ft_cd_hyphen(char **path, t_exec *vars)
{
	char	*tmp;
	int		pos;

	pos = srch_var_in_envp(vars->envp, "OLDPWD");
	if (pos == -1)
	{
		err_search_var(path, vars, "OLDPWD");
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

static int ft_cd_get_home(char **path, t_exec *vars, char *dir)
{
	int		i;
	char	*tmp;

	i = srch_var_in_envp(vars->envp, "HOME");
	if (i == -1)
	{
		if (!dir)
		{
			err_search_var(path, vars, "HOME");
			return (1);
		}
		return (0);
	}
	tmp = get_varvalue(vars->envp[i]);
	free(*path);
	*path = ft_strdup(tmp);
	return (0);
}

static int init_path(t_exec *vars, char	**path)
{
	int pos;

	pos = srch_var_in_envp(vars->envp, "PWD");
	if (pos == -1)
	{
		*path = getcwd(NULL, 0);
		if (!*path)
			return (-1);
	}
	else
	{
		*path = ft_strdup(get_varvalue(vars->envp[pos]));
		if (!*path)
		{
			err_search_var(path, vars, "PWD");
			return (1);
		}
	}
	return (0);
}

int	builtin_cd(char	*dir, t_exec *vars)
{
	char	*path;
	int res;

	res = init_path(vars, &path);
	if (res)
		return (res);
	if (dir && ft_strlen(dir) == 1 && dir[0] == '-')
		return (ft_cd_hyphen(&path, vars));
	if ((!dir || dir[0] == '~') && ft_cd_get_home(&path, vars, dir))
		return (1);
	if (dir && path)
		path = ft_cd_getpath(dir, &path);
	if (chdir(path))
	{
		free(path);
		return (-1);
	}
	chng_oldpwd(&path, vars);
	return (1);
}
