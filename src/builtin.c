/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/21 22:42:08 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*builtin_pwd(int sgn)
{
	char	*path;

	path = getcwd(NULL, 0);
	if(!sgn)
	{
		write(1, path, ft_strlen(path));
		free(path);
		path = NULL;
	}
	return (path);
}

void	builtin_env(char **envp)
{
	int	i;

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
*/

static void	builtin_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (cmd[i])
	{
		if (nl != -1 && !nl && cmd[i][0] == '-' && ft_strchr(cmd[i], 'n'))
			nl = 1;
		if (cmd[i][0] != '-')
			nl = -1;
		if (nl == -1)
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			write(1, " ", 1);
		}
		i++;
	}
	if (nl != 1)
		write(1, "\n", 1);
}

int builtin_check(char **cmd, t_exec *vars)
{
	int	len_cmd;

	len_cmd = ft_strlen(cmd[0]);
	if (len_cmd == 6 && !ft_memcmp(cmd[0], "export", len_cmd))
		//для экспорта может быть несколько значений
		builtin_export(vars, cmd[1]);	//скорее всего этот билтин отсюда надо убрать, т.к. его надо делать до форков, и лучше до экзекютора
	else if (len_cmd == 5 && !ft_memcmp(cmd[0], "unset", len_cmd))
		//для ансет может быть несколько значений
		builtin_unset(vars, cmd[1]);	//скорее всего этот билтин отсюда надо убрать, т.к. его надо делать до форков, и лучше до экзекютора
	else if (len_cmd == 4)
	{
		if (!ft_memcmp(cmd[0], "echo", len_cmd))
			builtin_echo(cmd);
		if (!ft_memcmp(cmd[0], "exit", len_cmd))
			; //Дописать
	}
	else if (len_cmd == 3)
	{
		if (!ft_memcmp(cmd[0], "env", len_cmd))
			builtin_env(vars->envp);
		if (!ft_memcmp(cmd[0], "pwd", len_cmd))
			builtin_pwd(0);
	}
	else if (len_cmd == 2 && !ft_memcmp(cmd[0], "cd", len_cmd))
		builtin_cd(cmd[1], vars->envp);
	return (0);
}

