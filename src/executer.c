/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/10 22:05:30 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int ft_exec(t_exec *vars, t_cmd *tmp)
// {
// 	return(execve(vars->path, tmp->cmd, vars->envp));
// }

static int call_parent(t_exec *vars)
{
	t_cmd *tmp;
	int res;

	tmp = vars->cmds;
	while (--vars->st)
		tmp = tmp->next;
	//здесь сделать обработку редиректов
	redirection_fd(tmp->v_rdr); //дописать обработку ошибок

	//здесь сделать проверку на built-in и их выполнение. В случае, если это не они, выполнять то, что ниже
	res = builtin_check(tmp->cmd, vars); 	//дописать обработку ошибок
	if (!res)
	{
		vars->path = get_path(vars->envp, tmp->cmd[0]);
		if (!vars->path)
		{
			ft_frmtrx(tmp->cmd);		//как сделать очистку в некоторой общей структуре
			//сделать очистку списков и замолоченных структур
			//здесь подумать на счет выхода
			ft_exit(0, "The path to execute the parent command was not found.");
		}
		printf("path= %s | cmd= %s | envp= %s\n", vars->path, tmp->cmd[0], vars->envp[0]);
		execve(vars->path, tmp->cmd, vars->envp);
/*		if (execve(vars->path, tmp->cmd, vars->envp) == -1)
		{
			// printf("%s: err\n", tmp->cmd[0]);
			printf("050505\n");
			free(vars->path);
			ft_frmtrx(tmp->cmd);
			//сделать очистку списков и замолоченных структур
			//здесь подумать на счет выхода
			printf("01010101\n");
			ft_exit(errno, NULL);
		}
*/		printf("020202020202\n");
		free(vars->path);
	}
	ft_frmtrx(tmp->cmd);
	//сделать очистку списков и замолоченных структур
	//закрыть и удалить временнй файл heredoc
	printf("030303\n");
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
	int fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
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
	printf("050505\n");
	call_parent(vars);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	return (0);
}
