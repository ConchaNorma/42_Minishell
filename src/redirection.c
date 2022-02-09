/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:28:34 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/09 19:40:05 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void redir_out(t_exec *vars)
{
	//открыть файл со стиранием данных и созданием в случае отсутствия
	//прописать обработку ошибок

	//как быть при перенаправлении на один STDIN/STDOUT/STDERR
}

static void redir_inp(t_exec *vars)
{

}

static void redir_apn(t_exec *vars)
{

}

static void redir_heredoc(t_exec *vars)
{
	//ридлайном счит
}

int redirection_fd(t_exec *vars)
{
	int i;

	i = 0;
	while (vars->cmds[vars->st]->v_rdr[i])
	{
		if (vars->cmds[vars->st]->v_rdr[i]->type == OUT)
			;
		else if (vars->cmds[vars->st]->v_rdr[i]->type == INP)
			;
		else if (vars->cmds[vars->st]->v_rdr[i]->type == APN)
			;
		else if (vars->cmds[vars->st]->v_rdr[i]->type == HRD)
			;
		else
			//Здесь возврат ошибки или завершение с ошибкой
			;
		i++;
	}
	return (0);
}
