/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/17 22:21:56 by aarnell          ###   ########.fr       */
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
		close(vars->pfd[0]);
		dup2(vars->pfd[1], 1);
		close(vars->pfd[1]);
	}
	return (0);
}

static int call_child(t_exec *vars)
{
	redir_base(vars);
	if (redirection_fd(vars->tm_cmd->v_rdr) == -1)
		err_exit(vars, 1);
	if (!builtin_check_exec(vars))	//прописать обработку ошибок и выход внутр и самих билтин
	{
		vars->path = get_path(vars->envp, vars->tm_cmd->cmd[0]);
		if (!vars->path)
			err_exit(vars, 1);
		if (execve(vars->path, vars->tm_cmd->cmd, vars->envp) == -1)
			err_exit(vars, 1);
	}
	clean_base_struct(vars, 1);
	exit(0);
	return (0);
}

static int call_parent(t_exec *vars)
{
	int status;

	if (vars->tm_cmd != vars->cmds)
	{
		close(vars->tfd[0]);
		close(vars->tfd[1]);
	}
	vars->tfd[0] = vars->pfd[0];
	vars->tfd[1] = vars->pfd[1];
	if(waitpid(vars->pid, &status, WUNTRACED) == -1)
		return (-1);		//дописать норм выход с очисткой и выводом ошибки, как в баш
		//тут выхода не будет, программа уйдет на след. итерацию
	//сделать обработку сигналов от дочерних процессов
	// if (status == SIGINT || status == SIGQUIT)
	// 	signal_handler(status);
	// if (WIFEXITED(status))
	// 	g_status = WEXITSTATUS(status);
	return (0);
}

static int exec_cmd(t_exec *vars)
{
	if (vars->tm_cmd->next && pipe(vars->pfd) == -1)
		return (-1);
	vars->pid = fork();		//дописать проверку на ошибку
	if (vars->pid == -1)
		return (-1);
	if (!vars->pid)
		call_child(vars);	//обработка ошибок?
	return (call_parent(vars));
}

int executer(t_exec *vars)
{
	vars->ofd[0] = dup(0);
	vars->ofd[1] = dup(1);
	vars->tm_cmd = vars->cmds;
	while (vars->tm_cmd)
	{
		if (vars->st == 1 && builtin_check_exec(vars))
			break ;
		if(exec_cmd(vars))
			return (-1);
		vars->tm_cmd = vars->tm_cmd->next;
	}
	dup2(vars->ofd[0], 0);
	dup2(vars->ofd[1], 1);
	close(vars->ofd[0]);
	close(vars->ofd[1]);
	return (0);
}
