/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:23:57 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/16 19:36:03 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit(int err, char *str)
{
	if (str)
	{
		write(2, "ERROR: ", 7);
		write(2, str, ft_strlen(str));
		write(2, "\n", 2);
	}
	else
		perror("ERROR");
	exit(err);
}

static void clean_lstcmd(t_exec *vars)
{
	// t_cmd	*l_cmd;
	// t_redir	*l_rdr;

	// версия 2
	t_cmd	*c_cmd;
	t_redir	*c_rdr;
	t_cmd	*t_cmd;
	t_redir	*t_rdr;

	// while (vars->cmds)
	// {
	// 	l_cmd = vars->cmds;
	// 	while (l_cmd->next)
	// 		l_cmd = l_cmd->next;
	// 	while (l_cmd->v_rdr)
	// 	{
	// 		l_rdr = l_cmd->v_rdr;
	// 		while (l_rdr->next)
	// 			l_rdr = l_rdr->next;
	// 		if (l_rdr->file)
	// 			free(l_rdr->file);
	// 		free(l_rdr);
	// 	}
	// 	if (l_cmd->cmd)
	// 		ft_frmtrx(l_cmd->cmd);
	// 	free(l_cmd);
	// }

	//версия 2
	if (vars->cmds)
	{
		c_cmd = vars->cmds;
		while (c_cmd)
		{
			t_cmd = c_cmd->next;
			if (c_cmd->v_rdr)
			{
				c_rdr = c_cmd->v_rdr;
				while (c_rdr)
				{
					t_rdr = c_rdr->next;
					if (c_rdr->file)
						free(c_rdr->file);
					free(c_rdr);
					c_rdr = t_rdr;
				}
			}
			if (c_cmd->cmd)
				ft_frmtrx(c_cmd->cmd);
			free(c_cmd);
			c_cmd = t_cmd;
		}
	}
}

void clean_base_struct(t_exec *vars, int exit)
{
	//саму структуру не очищать, т.к. выделена на стеке, только очистить переменные внутри
	//вероятно, вывод данных о ошибке стоит проводить до очистки, т.к. в переменных может быть нужная инфа

	if (vars->str)
		free(vars->str);
	vars->str = NULL;		//возможно зануление указателей вынести в отдельную функцию?
	if (vars->path)
		free(vars->path);
	vars->path = NULL;		//возможно зануление указателей вынести в отдельную функцию?
	if (vars->cmds)
		clean_lstcmd(vars);
	vars->cmds = NULL;
	//не нашел, где эта переменная используется, при очистке ломает прогу
	// if (vars->lvar)
	// 	ft_lstclear(&vars->lvar, free);
	// vars->lvar = NULL;

	//возможно нужно проверить не работает ли процесс по указанному пиду
	//Возможно пиды всех процессов записывать в некий массив, и принудительно завершать?
	//...Вряд ли, есть же фоновые процессы. Как быть, когда они  завершатся, если уже запущеныследующие команды
	vars->pid = -1;
	//Возможно стоит закрыть все fd'шники.
	//Для удобства - они должны при инициализации быть -1, чтобы не закрыть лишнее
	//Вероятно, перед закрытием нужно проверить, а открыты ли
	vars->ofd[0] = -1;
	vars->ofd[1] = -1;
	vars->pfd[0] = -1;
	vars->pfd[1] = -1;
	vars->tfd[0] = -1;
	vars->tfd[1] = -1;

	vars->st = -1;
	//envp чистить в конце и только в случае выхода из программы
	if (exit)
		ft_frmtrx(vars->envp);
}
