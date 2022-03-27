/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:09:20 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/27 20:28:27 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int builtin_cd(char	*dir, t_exec *vars)
{
	char	*path;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		len;

	path = getcwd(NULL, 0);
	if (!path)
		return (-1);
	tmp = NULL;
	i = srch_var_in_envp(vars->envp, "OLDPWD");
	if (dir && ft_strlen(dir) == 1 && dir[0] == '-')
	{
		if (i == -1)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			if (!vars->pid)
			{
				free(path);
				ft_errfrex(vars, FREX, 1, NULL);
			}
			vars->exit_status = 1;
			return (1);
		}
		tmp = ft_strdup(get_varvalue(vars->envp[i]));
		if (chdir(tmp))
		{
			free(tmp);
			free(path);
			return (-1);
		}
		tmp2 = ft_strjoin("OLDPWD=", path);
		find_repl_val_var_in_envp(vars->envp, tmp2);
		ft_putendl_fd(tmp, 1);
		free(tmp);
		free(tmp2);
		free(path);
		return (1);
	}
	i = 0;
	if (!dir || dir[0] == '~')
	{
		while (vars->envp[i])
		{
			tmp = ft_strnstr(vars->envp[i], "HOME=", 5);
			if (tmp)
			{
				free(path);
				path = ft_strdup(tmp + 5);
				break ;
			}
			i++;
		}
	}
	if (dir)
	{
		len = ft_strlen(dir);
		if (dir[0] == '/')
		{
			free(path);
			path = NULL;
		}
		i = 0;
		while (i < len)
		{
			if (dir[i] == '/')
				i++;
			if (dir[i] == '.' || dir[i] == '~')
			{
				if (!dir[i + 1])
					break ;
				if (dir[i + 1] == '/')
				{
					i++;
					continue ;
				}
				if(dir[i] == '.' && dir[i + 1] == '.' && (!dir[i + 2] || dir[i + 2] == '/'))
				{
					tmp = ft_strrchr(path, '/');
					tmp = ft_substr(path, 0, (tmp - path));
					free(path);
					path = tmp;
					i += 2;
					continue ;
				}
			}
			tmp = ft_strjoin(path, "/");
			free(path);
			path = tmp;
			if (dir[i])
			{
				tmp = ft_strchr((dir + i), '/');
				if (tmp)
				{
					tmp2 = ft_substr(dir, i, (tmp - (dir + i)));
					i += (tmp - (dir + i));
					tmp = ft_strjoin(path, tmp2);
					free(tmp2);
					free(path);
					path = tmp;
				}
				else
				{
					tmp2 = ft_substr(dir, i, ft_strlen((dir + i)));
					i += ft_strlen((dir + i));
					tmp = ft_strjoin(path, tmp2);
					free(tmp2);
					free(path);
					path = tmp;
				}
			}
		}
	}
	if (chdir(path))
	{
		free(path);
		return (-1);
	}
	i = srch_var_in_envp(vars->envp, "PWD");
	tmp = ft_strjoin("OLDPWD=", get_varvalue(vars->envp[i]));
	find_repl_val_var_in_envp(vars->envp, tmp);
	free(tmp);
	tmp = ft_strjoin("PWD=", path);
	find_repl_val_var_in_envp(vars->envp, tmp);
	free(tmp);
	free(path);
	return (1);
}
