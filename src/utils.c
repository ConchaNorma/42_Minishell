/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:23:57 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/20 21:16:37 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(int err, char *str)
{
	if (str)
	{
		write(2, "ERROR: ", 7);
		write(2, str, ft_strlen(str));
		write(2, "\n", 2);
	}
	else
		perror("ERROR");
	exit(err);
}

static char	*search_path(char *s_path, char *cmd)
{
	char	*res;
	char	*res2;
	char	**path;
	int		j;

	j = 0;
	path = ft_split(s_path, ':');
	while (path[j])
	{
		res = ft_strjoin(path[j], "/");
		res2 = ft_strjoin(res, cmd);
		if (access(res2, 0) == 0)
		{
			free(res);
			ft_frmtrx(path);
			return (res2);
		}
		free(res);
		free(res2);
		j++;
	}
	if (path)
		ft_frmtrx(path);
	return (NULL);
}

char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	*rs;

	i = 0;
	while (envp[i] && cmd[0] != '/' && cmd[0] != '.')
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			rs = search_path(envp[i] + 5, cmd);
			if (rs)
				return (rs);
		}
		i++;
	}
	if (cmd[0] == '/' || cmd[0] == '.')
		if (access(cmd, 0) == 0)
			return (cmd);
	return (NULL);
}

int srch_var_in_envp(char **envp, char *var_name)
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

char *get_varname(char *var_str, int with_eq)
{
	char	*eq;
	int		len;

	eq = ft_strchr(var_str, '=');
	if(!eq)
		return (NULL);
	len = eq - var_str + with_eq;
	return(ft_substr(var_str, 0, len));
}

char *get_varvalue(char *var_str)
{
	char	*eq;

	eq = ft_strchr(var_str, '=');
	if(!eq)
		return (NULL);
	return(eq + 1);
}
