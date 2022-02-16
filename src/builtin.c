/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/16 20:01:48 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *builtin_pwd(int sgn)
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

int builtin_cd(char *dir, char **envp)
{
	char	*path;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		len;

	path = builtin_pwd(1);
	tmp = NULL;
	i = 0;
	len = ft_strlen(dir);
	if (!dir || !len || dir[0] == '~')
	{
		while (envp[i])
		{
			tmp = ft_strnstr(envp[i], "HOME=", 5);
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
	//printf("path = %s\n", path);
	chdir(path);	//дописать обработку ошибок
	//printf("pwd = %s\n", builtin_pwd(1));
	free(path);
	return (0);
}

static void builtin_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}
/*
static int builtin_exit(void);
static int builtin_echo(void);
static int builtin_unset(void);
static int builtin_export(void);
*/
int builtin_check(char **cmd, char **envp)
{
	int len_cmd;

	len_cmd = ft_strlen(cmd[0]);
	if (len_cmd == 6 && !ft_memcmp(cmd[0], "export", len_cmd))
		;
	else if (len_cmd == 5 && !ft_memcmp(cmd[0], "unset", len_cmd))
		;
	else if (len_cmd == 4)
	{
		if (!ft_memcmp(cmd[0], "echo", len_cmd))
			;
		if (!ft_memcmp(cmd[0], "exit", len_cmd))
			;
	}
	else if (len_cmd == 3)
	{
		if (!ft_memcmp(cmd[0], "env", len_cmd))
			;
		if (!ft_memcmp(cmd[0], "pwd", len_cmd))
			builtin_pwd(0);
	}
	else if (len_cmd == 2 && !ft_memcmp(cmd[0], "cd", len_cmd))
		builtin_cd(cmd[1], envp);
	return (0);
}

