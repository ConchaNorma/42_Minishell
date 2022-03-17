/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:23:57 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/17 20:28:47 by aarnell          ###   ########.fr       */
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

int err_exit(t_exec *vars, int ext)
{
	perror("ERROR");	//вывод ошибки сделать идентично башу
	clean_base_struct(vars, ext);
	if (ext);
		exit(errno);
	return (1);
}

static void clean_lstcmd(t_exec *vars)
{
	t_cmd	*c_cmd;
	t_redir	*c_rdr;
	t_cmd	*t_cmd;
	t_redir	*t_rdr;

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

void clean_base_struct(t_exec *vars, int ext)
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
	if (ext)
		ft_frmtrx(vars->envp);
}
