/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_getpath.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:15:20 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/03 18:09:43 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_if_dot_or_wave(char	*dir, int *i, char **path)
{
	char	*tmp;

	if (dir[*i] == '.' || dir[*i] == '~')
	{
		if (!dir[*i + 1])
			return (-1);
		if (dir[*i + 1] == '/')
		{
			(*i)++;
			return (1);
		}
		if (dir[*i] == '.' && dir[*i + 1] == '.' \
			&& (!dir[*i + 2] || dir[*i + 2] == '/'))
		{
			tmp = ft_strrchr(*path, '/');
			tmp = ft_substr(*path, 0, (tmp - *path));
			free(*path);
			*path = tmp;
			*i = *i + 2;
			return (1);
		}
	}
	return (0);
}

static void	ft_cnct_nxt_stg(char *dir, int *i, char **path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strchr((dir + *i), '/');
	if (tmp)
	{
		tmp2 = ft_substr(dir, *i, (tmp - (dir + *i)));
		*i = *i + (tmp - (dir + *i));
	}
	else
	{
		tmp2 = ft_substr(dir, *i, ft_strlen((dir + *i)));
		*i = *i + ft_strlen((dir + *i));
	}
	tmp = ft_strjoin(*path, tmp2);
	free(tmp2);
	free(*path);
	*path = tmp;
}

static void	ft_cnct_slash(char **path)
{
	char	*tmp;

	tmp = ft_strjoin(*path, "/");
	free(*path);
	*path = tmp;
}

char	*ft_cd_getpath(char	*dir, char **path)
{
	int		i;
	int		res;

	if (dir[0] == '/')
	{
		free(*path);
		*path = NULL;
	}
	i = 0;
	while (i < (int)ft_strlen(dir))
	{
		if (dir[i] == '/')
			i++;
		res = ft_if_dot_or_wave(dir, &i, path);
		if (res == -1)
			break ;
		if (res == 1)
			continue ;
		ft_cnct_slash(path);
		if (dir[i])
			ft_cnct_nxt_stg(dir, &i, path);
	}
	return (*path);
}

void	chng_oldpwd(char **path, t_exec *vars)
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
