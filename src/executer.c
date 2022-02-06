/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/06 15:07:09 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static char	*get_path(char **envp, char *cmd)
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

static int call_parent(t_exec *vars)
{
	vars->st--;
	//здесь сделай функцию работы с редиректами
	vars->cmd = ft_split(vars->cmds[vars->st]->cmd, ' ');
	vars->path = get_path(vars->envp, vars->cmd[0]);
	if (!vars->path)
	{
		ft_frmtrx(vars->cmd);
		//здесь подумать на счет выхода
		//ft_exit(0, "The path to execute the parent command was not found.");
	}
	if (execve(vars->path, vars->cmd, vars->envp) == -1)
	{
		free(vars->path);
		ft_frmtrx(vars->cmd);
		//здесь подумать на счет выхода
		//ft_exit(errno, NULL);
	}
	free(vars->path);
	ft_frmtrx(vars->cmd);
	close(vars->fd[0]);
	return (0);
}

static int call_child(t_exec *vars)
{
	vars->st--;
	close(vars->fd[0]);
	dup2(vars->fd[1], 1); //написать проверку
	executer(vars);
	return (0);
}

int executer(t_exec *vars)
{
	if(vars->st > 1)
	{
		pipe(vars->fd);
		vars->pid = fork();
		//дописать проверку ошибок двух строк выше
		if(!vars->pid)
			return(call_child(vars));
		else
		{
			close(vars->fd[1]);
			dup2(vars->fd[0], 0);	//дописать проверку на ошибку
			waitpid(vars->pid, NULL, WUNTRACED);
		}
	}
	return (call_parent(vars));
}
