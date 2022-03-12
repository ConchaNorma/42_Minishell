/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/12 21:55:05 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int redir_base(t_exec *vars)
{
	if (vars->tm_cmd != vars->cmds)
	{
		close(vars->tfd[1]);
		dup2(vars->tfd[0], 0);
		close(vars->tfd[0]);
	}
	if (vars->tm_cmd->next)
	{
		close(vars->fd[0]);
		dup2(vars->fd[1], 1);
		close(vars->fd[1]);
	}
	return (0);
}

static int call_child(t_exec *vars)
{
	int res;

	if (vars->st > 1)
		redir_base(vars); //дописать проверку
	redirection_fd(vars->tm_cmd->v_rdr); //дописать обработку ошибок
	res = builtin_check(vars); 	//дописать обработку ошибок
	if (!res)
	{
		vars->path = get_path(vars->envp, vars->tm_cmd->cmd[0]);
		if (!vars->path)
		{
			// ft_frmtrx(tmp->cmd);		//как сделать очистку в некоторой общей структуре
			//сделать очистку списков и замолоченных структур
			//здесь подумать на счет выхода
			ft_exit(0, "The path to execute the parent command was not found.");
		}
		if (execve(vars->path, vars->tm_cmd->cmd, vars->envp) == -1)
		{
			free(vars->path);
			// ft_frmtrx(tmp->cmd);
			//сделать очистку списков и замолоченных структур
			//здесь подумать на счет выхода
			ft_exit(errno, NULL);
		}
		free(vars->path);
	}
	//сделать очистку списков и замолоченных структур
	//закрыть и удалить временнй файл heredoc
	return (0);
}

int executer(t_exec *vars)
{
	int op[2];

	op[0] = dup(0);
	op[1] = dup(1);
	vars->tm_cmd = vars->cmds;
	while (vars->tm_cmd)
	{
		if (vars->st > 1)
		{
			if (vars->tm_cmd->next)
				pipe(vars->fd);			//дописать проверку на ошибку
			vars->pid = fork();		//дописать проверку на ошибку
			if (!vars->pid)
			{
				call_child(vars);
				exit(0);
			}
			else
			{
				if (vars->tm_cmd != vars->cmds)
				{
					close(vars->tfd[0]);
					close(vars->tfd[1]);
				}
				vars->tfd[0] = vars->fd[0];
				vars->tfd[1] = vars->fd[1];
				waitpid(vars->pid, NULL, WUNTRACED); //дописать провекрку ошибок
			}
		}
		else
			call_child(vars);
		vars->tm_cmd = vars->tm_cmd->next;
	}
	dup2(op[0], 0);
	dup2(op[1], 1);
	close(op[0]);
	close(op[1]);
	return (0);
}
