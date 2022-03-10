/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/09 21:07:51 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int redir_base(t_exec *vars, int i)
{
	ft_putstr_fd("0redir", vars->tfd[1]);
	ft_putnbr_fd(i, vars->tfd[1]);
	write(vars->tfd[1], "\n", 1);
	// if (!i)
	// 	dup2(vars->tfd[0], 0);
	if (i)
	{
		//vars->tfd[0] = dup(0);
		close(vars->fd[1]);
		dup2(vars->tfd[2], 0);
		close(vars->tfd[2]);
	}
	// if (i == (vars->st - 1))
	//  	dup2(vars->tfd[1], 1);
	if (i != (vars->st - 1))
	{
		// vars->tfd[1] = dup(1);
		close(vars->fd[0]);
		dup2(vars->fd[1], 1);
		close(vars->fd[1]);
	}
	ft_putstr_fd("1redir", vars->tfd[1]);
	ft_putnbr_fd(i, vars->tfd[1]);
	write(vars->tfd[1], "\n", 1);
	//ft_putstr_fd("huy\n", vars->tfd[1]);
	//Записать stdin/stdout
	//Назначить для fd'шников pipe stdin/stdout
	//В последнем процессе вернуть stdin/stdout на место

	//Для первого процесса
	//Для среднего процесса

	//Для последнего процесса



	//добавить обработку ошибок dup'ов
	return (0);
}

static int call_child(t_exec *vars, int i)
{
	t_cmd *tmp;
	int res;
	//char buf[100];


	//это выполняется только в случае, если конвейеров больше 1
	if (vars->st > 1)
		redir_base(vars, i); //дописать проверку
	tmp = vars->cmds;
	while (i--)
		tmp = tmp->next;
	redirection_fd(tmp->v_rdr); //дописать обработку ошибок
	res = builtin_check(tmp->cmd, vars); 	//дописать обработку ошибок
	// ft_putstr_fd("pre!res", vars->tfd[1]);
	// ft_putnbr_fd(i, vars->tfd[1]);
	// write(vars->tfd[1], "\n", 1);
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
		ft_putstr_fd("mid!res", vars->tfd[1]);
		ft_putnbr_fd(i, vars->tfd[1]);
		write(vars->tfd[1], "\n", 1);

		if (execve(vars->path, tmp->cmd, vars->envp) == -1)
		{
			//printf("%s: err\n", tmp->cmd[0]);
			free(vars->path);
			ft_frmtrx(tmp->cmd);
			//сделать очистку списков и замолоченных структур
			//здесь подумать на счет выхода
			ft_exit(errno, NULL);
		}
		// printf("nnn\n");
		free(vars->path);
	}
	ft_frmtrx(tmp->cmd);
	ft_putstr_fd("fin!res", 2); //vars->tfd[1]);
	ft_putnbr_fd(i, vars->tfd[1]);
	write(vars->tfd[1], "\n", 1);
	//сделать очистку списков и замолоченных структур
	//закрыть и удалить временнй файл heredoc
	/*if (vars->st > 1)
	{
		close(vars->tfd[2]);
		close(vars->fd[1]);
	}*/

	return (0);
}

int executer(t_exec *vars)
{
	int i;

	i = 0;
	vars->tfd[0] = dup(0);
	vars->tfd[1] = dup(1);
	while (i < vars->st)
	{
		if (vars->st > 1)
		{
			// if (i != (vars->st - 1))
			// {
				pipe(vars->fd);			//дописать проверку на ошибку
				vars->tfd[2] = vars->fd[0];
			// }
			printf("prefork. i = %d\n", i);
			vars->pid = fork();		//дописать проверку на ошибку
			if (!vars->pid)
			{
				call_child(vars, i);
				exit(0);
				//return(call_child(vars, i));
			}
			else
				waitpid(vars->pid, NULL, WUNTRACED);
		}
		else
			call_child(vars, i);
		i++;
	}
	dup2(vars->tfd[0], 0);
	dup2(vars->tfd[1], 1);
	printf("fin.\n");
	return (0);
}
