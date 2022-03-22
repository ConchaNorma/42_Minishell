/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/22 22:29:28 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void call_child(t_exec *vars)
{
	int res;

	redir_base(vars);
	if (redirection_fd(vars->tm_cmd->v_rdr) == -1)
		ft_errfrex(vars, ERFREX, 1, NULL);
	res = builtin_check_exec(vars);
	if (res == -1)
		ft_errfrex(vars, ERFREX, 1, NULL);
	if (!res)
	{
		vars->path = get_path(vars->envp, vars->tm_cmd->cmd[0]);
		if (!vars->path)
			ft_errfrex(vars, ERFREX, 1, NULL);
		if (execve(vars->path, vars->tm_cmd->cmd, vars->envp) == -1)
		{
			if (errno == 2)
				ft_errfrex(vars, ERFREX, 127, NULL);
			ft_errfrex(vars, ERFREX, 1, NULL);
		}
	}
	ft_errfrex(vars, FREX, 0, NULL);
}

static int call_parent(t_exec *vars)
{
	if (vars->tm_cmd != vars->cmds)
	{
		close(vars->tfd[0]);
		close(vars->tfd[1]);
	}
	vars->tfd[0] = vars->pfd[0];
	vars->tfd[1] = vars->pfd[1];
	if(waitpid(vars->pid, &vars->exit_status, WUNTRACED) == -1)
		return (-1);
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
	int res;

	res = 0;
	vars->pid = -1;
	vars->ofd[0] = dup(0);
	vars->ofd[1] = dup(1);
	vars->tm_cmd = vars->cmds;
	while (vars->tm_cmd)
	{
		if (vars->st == 1)
		{
			res = builtin_check_exec(vars);
			if (res)
				break ;
		}
		res = exec_cmd(vars);
		if(res == -1)
			break ;
		vars->tm_cmd = vars->tm_cmd->next;
	}
	dup2(vars->ofd[0], 0);
	dup2(vars->ofd[1], 1);
	close(vars->ofd[0]);
	close(vars->ofd[1]);
	return (res);
}
