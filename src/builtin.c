/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/04 00:49:08 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (-1);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return (1);
}

int	builtin_env(t_exec *vars)
{
	int	i;

	if (srch_var_in_envp(vars->envp, "PATH") == -1)
	{
		ft_putendl_fd("minishell: env: No such file or directory", 2);
		ft_errfrex(vars, FREX, 127, NULL);
	}
	i = 0;
	while (vars->envp[i])
	{
		ft_putendl_fd(vars->envp[i], 1);
		i++;
	}
	return (1);
}

int	builtin_check_exec(t_exec *vars)
{
	int		ln;
	char	**cmd;

	cmd = vars->tm_cmd->cmd;
	ln = ft_strlen(cmd[0]);
	if (!ft_memcmp(cmd[0], "export", ln))
		return (builtin_export(vars, cmd));
	else if (!ft_memcmp(cmd[0], "unset", ln))
		return (builtin_unset(vars, cmd));
	else if (!vars->pid && !ft_memcmp(cmd[0], "echo", ln))
		return (builtin_echo(cmd));
	else if (!ft_memcmp(cmd[0], "exit", ln))
		builtin_exit(vars, cmd);
	else if (!vars->pid && !ft_memcmp(cmd[0], "env", ln))
		return (builtin_env(vars));
	else if (!vars->pid && !ft_memcmp(cmd[0], "pwd", ln))
		return (builtin_pwd());
	else if (!ft_memcmp(cmd[0], "cd", ln))
		return (builtin_cd(cmd[1], vars));
	return (0);
}
