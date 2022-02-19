/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:09:20 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/19 12:12:59 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
