/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/03 20:01:51 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	call_child(t_exec *vars)
{
	int	res;

	vars->exit_status = 0;
	redir_base(vars);
	if (redirection_fd(vars->tm_cmd->v_rdr, vars->ofd[0]) == -1)
		ft_errfrex(vars, ERFREX, 1, NULL);
	res = builtin_check_exec(vars);
	if (res == -1)
		ft_errfrex(vars, ERFREX, 1, NULL);
	if (!res)
	{
		vars->path = get_path(vars->envp, vars->tm_cmd->cmd[0]);
		if (!vars->path)
			ft_errfrex(vars, ERFREX, 127, NULL);
		if (execve(vars->path, vars->tm_cmd->cmd, vars->envp) == -1)
		{
			if (errno == 2)
				ft_errfrex(vars, ERFREX, 127, NULL);
			ft_errfrex(vars, ERFREX, 1, NULL);
		}
	}
	ft_errfrex(vars, FREX, vars->exit_status, NULL);
}

static void	ft_close_double_fd(int *fd)
{
	int	i;

	i = -1;
	while (++i < 2)
		close(fd[i]);
}

static void	exec_data_change(t_exec *vars, int *res, int *i, int part)
{
	if (part == 0)
	{
		*res = 0;
		vars->ofd[0] = dup(0);
		vars->ofd[1] = dup(1);
		vars->tm_cmd = vars->cmds;
		*i = 0;
	}
	else if (part == 1)
	{
		if (vars->tm_cmd != vars->cmds)
			ft_close_double_fd(vars->tfd);
		vars->tfd[0] = vars->pfd[0];
		vars->tfd[1] = vars->pfd[1];
		vars->tm_cmd = vars->tm_cmd->next;
		(*i)++;
	}
	else if (part == 2)
	{
		dup2(vars->ofd[0], 0);
		dup2(vars->ofd[1], 1);
		ft_close_double_fd(vars->ofd);
	}
}

static void	ft_wait(t_exec *vars)
{
	int	status;
	int	i;

	i = 0;
	while (i < vars->st)
	{
		if (waitpid(vars->pids[i], &status, WUNTRACED) == -1)
		{
			perror("minishell: ");
			ft_errfrex(vars, FREX, 1, NULL);
		}
		i++;
	}
	vars->exit_status = WEXITSTATUS(status);
}

int	executer(t_exec *vars)
{
	int		res;
	int		i;

	vars->pids = (pid_t *)malloc(sizeof(pid_t) * (vars->st));
	exec_data_change(vars, &res, &i, 0);
	if (vars->st == 1)
		res = builtin_check_exec(vars);
	while (!res && vars->tm_cmd)
	{
		if (vars->tm_cmd->next && pipe(vars->pfd) == -1)
			break ;
		vars->pids[i] = fork();
		vars->pid = vars->pids[i];
		if (vars->pid == -1)
			return (-1);
		if (!vars->pid)
			call_child(vars);
		exec_data_change(vars, &res, &i, 1);
	}
	if (!res)
		ft_wait(vars);
	exec_data_change(vars, &res, &i, 2);
	return (res);
}
