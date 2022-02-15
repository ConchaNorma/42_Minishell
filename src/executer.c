/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/15 20:33:52 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int call_parent(t_exec *vars)
{
	t_cmd *tmp;

	tmp = vars->cmds;
	//vars->st--;
	while (--vars->st)
		tmp = tmp->next;
	//здесь сделать обработку редиректов
	redirection_fd(tmp->v_rdr);
	//vars->exe = ft_split(tmp->cmd, ' ');
	//здесь сделать проверку на built-in и их выполнение. В случае, если это не они, выполнять то, что ниже
	builtin_check(tmp->cmd, vars->envp);
	vars->path = get_path(vars->envp, tmp->cmd[0]);
	if (!vars->path)
	{
		ft_frmtrx(tmp->cmd);		//как сделать очистку в некоторой общей структуре
		//сделать очистку списков и замолоченных структур
		//здесь подумать на счет выхода
		ft_exit(0, "The path to execute the parent command was not found.");
	}
	if (execve(vars->path, tmp->cmd, vars->envp) == -1)
	{
		free(vars->path);
		ft_frmtrx(tmp->cmd);
		//сделать очистку списков и замолоченных структур
		//здесь подумать на счет выхода
		ft_exit(errno, NULL);
	}
	free(vars->path);
	ft_frmtrx(tmp->cmd);
	//сделать очистку списков и замолоченных структур
	//закрыть и удалить временнй файл heredoc
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
