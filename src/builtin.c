/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:05:10 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/29 21:36:13 by aarnell          ###   ########.fr       */
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

static int exstat_hand(char **code, int res)
{
	char *tmp;
	char *tmp2;
	int ex_st;

	ex_st = 0;
	if (code[1] && !res)
		ex_st = ft_atoi(code[1]);
	if (!res)
	{
		if (code[1] && code[2])
			ft_putendl_fd("minishell: exit: too many arguments", 2);
		ex_st = (int)(unsigned char)ex_st;
	}
	else
	{
		tmp = ft_strjoin("minishell: exit: ", code[1]);
		tmp2 = ft_strjoin(tmp, ": numeric argument required");
		ft_putendl_fd(tmp2, 2);
		free(tmp);
		free(tmp2);
		ex_st = 255;
	}
	return (ex_st);
}

static void	builtin_exit(t_exec *vars, char **code)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (vars->st == 1)
		ft_putendl_fd("exit", 2);
	while (code[1] && code[1][i])
	{
		if (!i && code[1][i] == '-')
		{
			if (!code[1][i + 1])
			{
				res = 1;
				break ;
			}
			i++;
			continue ;
		}
		if (!ft_isdigit(code[1][i++]))
			res = 1;
	}
	res = exstat_hand(code, res);
	clean_base_struct(vars, 1);
	exit(res);
}

int builtin_check_exec(t_exec *vars)
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

