/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/21 22:28:30 by aarnell          ###   ########.fr       */
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

	// int i;

	// i = -1;
	// while (vars->cmds->cmd[++i])
	// 	printf("vars->cmds->cmd[%d] = %s\n", i, vars->cmds->cmd[i]);

	tmp = vars->cmds;
	//vars->st--;
	while (--vars->st)
		tmp = tmp->next;
	//здесь сделать обработку редиректов
	redirection_fd(tmp->v_rdr);

	// printf("len0 = %zu\n", ft_arrlen((void **)tmp->cmd));
	// tmp->cmd = ft_add_str_to_arr(tmp->cmd, "");
	// i = ft_arrlen((void **)tmp->cmd);
	// printf("len1 = %d\n", i);
	// tmp->cmd[i - 1] = NULL;
	// printf("len2 = %zu\n", ft_arrlen((void **)tmp->cmd));

	//здесь сделать проверку на built-in и их выполнение. В случае, если это не они, выполнять то, что ниже
	builtin_check(tmp->cmd, vars);
	vars->path = get_path(vars->envp, tmp->cmd[0]);
	if (!vars->path)
	{
		ft_frmtrx(tmp->cmd);		//как сделать очистку в некоторой общей структуре
		//сделать очистку списков и замолоченных структур
		//здесь подумать на счет выхода
		ft_exit(0, "The path to execute the parent command was not found.");
	}
	// printf("vars->path: %s\n", vars->path);
	// i = -1;
	// while (tmp->cmd[++i])
	// 	printf("tmp->cmd[%d] = %s\n", i, tmp->cmd[i]);

	//
	//if (ft_exec(vars, tmp) == -1)
	//if (execve(vars->path, cm, vars->envp) == -1)
	if (execve(vars->path, tmp->cmd, vars->envp) == -1)
	{
		// printf("%s: err\n", tmp->cmd[0]);
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
