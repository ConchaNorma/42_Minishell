/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:09:20 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/05 20:06:49 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static int	ft_cd_get_home(char **path, t_exec *vars, char *dir)
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

static int	init_path(t_exec *vars, char	**path)
{
	int	pos;

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
	int		res;

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

int	builtin_pwd(t_exec *vars)
{
	char	*path;
	int		res;

	res = init_path(vars, &path);
	if (res)
		return (res);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return (1);
}
