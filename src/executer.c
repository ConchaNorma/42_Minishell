/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/08 19:28:57 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int call_parent(t_exec *vars)
{
	vars->st--;
	//здесь сделай функцию работы с редиректами
	//void redirection_fd(vars);
	vars->cmd = ft_split(vars->cmds[vars->st]->cmd, ' ');
	//здесь сделать проверку на built-in и их выполнение. В случае, если это не они, выполнять то, что ниже
	vars->path = get_path(vars->envp, vars->cmd[0]);
	if (!vars->path)
	{
		ft_frmtrx(vars->cmd);
		//здесь подумать на счет выхода
		ft_exit(0, "The path to execute the parent command was not found.");
	}
	if (execve(vars->path, vars->cmd, vars->envp) == -1)
	{
		free(vars->path);
		ft_frmtrx(vars->cmd);
		//здесь подумать на счет выхода
		ft_exit(errno, NULL);
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
