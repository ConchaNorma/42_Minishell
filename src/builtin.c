/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/04 22:26:49 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0); //возможно нужна проверка на ошибку
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return (1);
}

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (1);
}

/*
static int builtin_exit(void);
*/

static int	builtin_echo(char **cmd)
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
	return (1);
}

int builtin_check(char **cmd, t_exec *vars)
{
	int	ln;

	ln = ft_strlen(cmd[0]);
	if (ln == 6 && !ft_memcmp(cmd[0], "export", ln))
		return(builtin_export(vars, cmd));	//возможно стоит дописать эту часть на случай 'v=123 export vv=234'
	else if (ln == 5 && !ft_memcmp(cmd[0], "unset", ln))
		return(builtin_unset(vars, cmd));
	else if (ln == 4 && !ft_memcmp(cmd[0], "echo", ln))
		return(builtin_echo(cmd));
	else if (ln == 4 && !ft_memcmp(cmd[0], "exit", ln))
		; //Дописать
	else if (ln == 3 && !ft_memcmp(cmd[0], "env", ln))
		return(builtin_env(vars->envp));
	else if (ln == 3 && !ft_memcmp(cmd[0], "pwd", ln))
		return(builtin_pwd());
	else if (ln == 2 && !ft_memcmp(cmd[0], "cd", ln))
		return(builtin_cd(cmd[1], vars->envp));
	return (0);
}

