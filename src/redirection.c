/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:28:34 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/09 22:33:22 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int redir_out(t_redir *v_rdr)
{
	//дописать: при открытии нового, закрывать старый
	//открыть файл со стиранием данных и созданием в случае отсутствия, и права на запись
	v_rdr->fd = open(v_rdr->file, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
	//прописать обработку ошибок
	//делаем редирект stdout на файл
	dup2(v_rdr->fd, 1);	//дописать обработку ошибок
	return (0);
	//как быть при перенаправлении на один STDIN/STDOUT/STDERR
}

static int redir_inp(t_redir *v_rdr)
{
	//дописать: при открытии нового, закрывать старый
	//открыть файл с правами на чтение
	v_rdr->fd = open(v_rdr->file, O_RDONLY, S_IREAD);
	//прописать обработку ошибок
	//делаем редирект stdin на файл
	dup2(v_rdr->fd, 0);	//дописать обработку ошибок
	return (0);
}

static int redir_apn(t_redir *v_rdr)
{
	//открыть файл без стирания данных и созданием в случае отсутствия, и права на запись
	v_rdr->fd = open(v_rdr->file, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
	//прописать обработку ошибок
	//делаем редирект stdout на файл
	dup2(v_rdr->fd, 1);
	return (0);
}

static int redir_heredoc(t_redir *v_rdr)
{
	char *str;
	int len;

	str = NULL;
	str = readline(">$ ");
	//цикл
	while (str)
	{
		//проверяем, не конец ли (если конец, чистим временную строку и завершаем цикл)
		len = ft_strlen(str);
		if(len < ft_strlen(v_rdr->file))
			len = ft_strlen(v_rdr->file);
		if(!ft_memcmp(str, v_rdr->file, len))
		{
			free(str);
			break ;
		}
		//пишем сроку в stdin
		write(0, str, ft_strlen(str));
		write(0, "\n", 1);
		//чистим строку
		free(str);
		//ридлайном считываем новую строку во временный указатель
		str = readline(">$ ");
	}
	return (0);		//нужно ли здесь где-то обработчик ошибок
}

int redirection_fd(t_exec *vars)
{
	int i;

	i = 0;
	while (vars->cmds[vars->st]->v_rdr[i])
	{
		if (vars->cmds[vars->st]->v_rdr[i]->type == OUT)
			redir_out(vars->cmds[vars->st]->v_rdr[i]);
		else if (vars->cmds[vars->st]->v_rdr[i]->type == INP)
			redir_inp(vars->cmds[vars->st]->v_rdr[i]);
		else if (vars->cmds[vars->st]->v_rdr[i]->type == APN)
			redir_apn(vars->cmds[vars->st]->v_rdr[i]);
		else if (vars->cmds[vars->st]->v_rdr[i]->type == HRD)
			redir_heredoc(vars->cmds[vars->st]->v_rdr[i]);
		i++;
	}
	return (0);	//возможно где-то здесь нужен обработчик ошибок
}
