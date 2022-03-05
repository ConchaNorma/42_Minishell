/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/05 22:11:34 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int call_child(t_exec *vars, int i)
{
	close(vars->fd[0]);
	if (i)
		dup2(vars->tfd[2], 0);	//написать проверку
	dup2(vars->fd[1], 1);		//написать проверку



	close(vars->tfd[2]);
	close(vars->fd[1]);
	return (0);
}

int executer(t_exec *vars)
{
	int i;

	vars->tfd[0] = dup(0);
	vars->tfd[1] = dup(1);
	i = 0;
	while (i < vars->st)
	{
		pipe(vars->fd);			//дописать проверку на ошибку
		vars->tfd[2] = vars->fd[0];
		vars->pid = fork();		//дописать проверку на ошибку
		if (!vars->pid)
			return(call_child(vars, i));
		else

		i++;
	}
	waitpid(-1, NULL, WUNTRACED);	//важно ли какого процесса ждать, проверка на ошибки, результат?
	dup2(vars->tfd[0], 0);
	dup2(vars->tfd[1], 1);
	close(vars->tfd[2]);
	return (0);
}
