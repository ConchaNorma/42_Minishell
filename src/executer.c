/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/16 22:06:35 by aarnell          ###   ########.fr       */
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
	// vars->ofd[0] = dup(0);
	// vars->ofd[1] = dup(1);
	redir_base(vars); //дописать проверку
	redirection_fd(vars->tm_cmd->v_rdr); //дописать обработку ошибок
	if (!builtin_check_exec(vars))	//прописать обработку ошибок и выход внутр и самих билтин
	{
		vars->path = get_path(vars->envp, vars->tm_cmd->cmd[0]);
		if (!vars->path)
		{
			// ft_frmtrx(tmp->cmd);		//как сделать очистку в некоторой общей структуре
			//сделать очистку списков и замолоченных структур
			//здесь подумать на счет выхода
			ft_exit(0, "The path to execute the parent command was not found.");		//ошибка должна как в баше
			//при ошибке минишел не должен вылетать
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
	// dup2(vars->ofd[0], 0);
	// dup2(vars->ofd[1], 1);
	// close(vars->ofd[0]);
	// close(vars->ofd[1]);
	exit(0);	//здесь дописать нормальный выход с очисткой
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
		ft_exit(errno, NULL);		//дописать норм выход с очисткой и выводом ошибки, как в баш
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
	{
		//ft_exit(errno, NULL);	//дописать нормальный выход с очисткой и выводом ошибки
		perror("ERROR");
		return (1);
	}
	vars->pid = fork();		//дописать проверку на ошибку
	if (!vars->pid)
		call_child(vars);	//обработка ошибок?
	else
		call_parent(vars);	//обработка ошибок?
	return (0);
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
			return (1);
		vars->tm_cmd = vars->tm_cmd->next;
	}
	dup2(vars->ofd[0], 0);
	dup2(vars->ofd[1], 1);
	close(vars->ofd[0]);
	close(vars->ofd[1]);
	return (0);
}
