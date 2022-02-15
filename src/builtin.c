/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/13 20:54:19 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char *builtin_pwd(int sgn)
{
	char *path;

	path = getcwd(NULL, 0);
	if(!sgn)
	{
		write(1, path, ft_strlen(path));
		free(path);
		path = NULL;
	}
	return (path);
}

int builtin_cd(char *exe, char **envp)
{
	char	*path;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		len;

	path = builtin_pwd(1);
	tmp = NULL;
	i = 0;
	len = ft_strlen(exe);
	if (!exe || exe[0] == '~')
	{
		while (envp[i])
		{
			tmp = ft_strnstr(envp[i], "HOME=", 5);
			if (tmp)
			{
				free(path);
				path = ft_strdup(tmp);
				break ;
			}
			i++;
		}
	}
	if (exe)
	{
		if (exe[0] == '/')
		{
			free(path);
			path = NULL;
		}
		i = 0;
		while (i < len)
		{
			if (exe[i] == '/')
				i++;
			if (exe[i] == '.' || exe[i] == '~')
			{
				if (!exe[i + 1])
					break ;
				if (exe[i + 1] == '/')
				{
					i++;
					continue ;
				}
				if(exe[i] == '.' && exe[i + 1] == '.' && (!exe[i + 2] || exe[i + 2] == '/'))
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
			if (exe[i])
			{
				tmp = ft_strrchr((exe + i), '/');
				if (tmp)
				{
					tmp2 = ft_substr(exe, i, (tmp - (exe + i)));
					i += (tmp - (exe + i));
					tmp = ft_strjoin(path, tmp2);
					free(tmp2);
					free(path);
					path = tmp;
				}
				else
				{
					tmp2 = ft_substr(exe, i, ft_strlen((exe + i)));
					i += ft_strlen((exe + i));
					tmp = ft_strjoin(path, tmp2);
					free(tmp2);
					free(path);
					path = tmp;
				}
			}
		}
	}
	printf("path = %s\n", path);
	//chdir(path);	//дописать обработку ошибок
	free(path);
	return (0);
}
/*
static int builtin_env(void);
static int builtin_exit(void);
static int builtin_echo(void);
static int builtin_unset(void);
static int builtin_export(void);
*/
int builtin_check(t_exec *vars)
{
	int len_cmd;

	len_cmd = ft_strlen(vars->exe[0]);
	if (len_cmd == 6 && !ft_memcmp(vars->exe[0], "export", len_cmd))
		;
	else if (len_cmd == 5 && !ft_memcmp(vars->exe[0], "unset", len_cmd))
		;
	else if (len_cmd == 4)
	{
		if (!ft_memcmp(vars->exe[0], "echo", len_cmd))
			;
		if (!ft_memcmp(vars->exe[0], "exit", len_cmd))
			;
	}
	else if (len_cmd == 3)
	{
		if (!ft_memcmp(vars->exe[0], "env", len_cmd))
			;
		if (!ft_memcmp(vars->exe[0], "pwd", len_cmd))
			builtin_pwd(0);
	}
	else if (len_cmd == 2 && !ft_memcmp(vars->exe[0], "cd", len_cmd))
		builtin_cd(vars->exe[1], vars->envp);
	return (0);
}

