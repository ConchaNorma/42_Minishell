/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:28:34 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/13 19:31:33 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int redir_out(t_redir *v_rdr)
{
	int fd;
	//дописать: при открытии нового, закрывать старый - не надо, dup закроет
	//открыть файл со стиранием данных и созданием в случае отсутствия, и права на запись
	fd = open(v_rdr->file, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
	//прописать обработку ошибок
	//делаем редирект stdout на файл
	dup2(fd, 1);	//дописать обработку ошибок
	return (0);
	//как быть при перенаправлении на один STDIN/STDOUT/STDERR
}

static int redir_inp(t_redir *v_rdr)
{
	int fd;
	//дописать: при открытии нового, закрывать старый
	//открыть файл с правами на чтение
	fd = open(v_rdr->file, O_RDONLY, S_IREAD);
	//прописать обработку ошибок
	//делаем редирект stdin на файл
	dup2(fd, 0);	//дописать обработку ошибок
	return (0);
}

static int redir_apn(t_redir *v_rdr)
{
	int fd;
	//открыть файл без стирания данных и созданием в случае отсутствия, и права на запись
	fd = open(v_rdr->file, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
	//прописать обработку ошибок
	//делаем редирект stdout на файл
	dup2(fd, 1);
	return (0);
}

static int redir_heredoc(t_redir *v_rdr)
{
	char *str;
	size_t len;
	int fd;

	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
	//прописать обработку ошибок
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
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		//чистим строку
		free(str);
		//ридлайном считываем новую строку во временный указатель
		str = readline(">$ ");
	}
	write(fd, "\0", 1); //нужно ли это для обозначения конца файла
	dup2(fd, 0);	//прописать обработку ошибок
	return (0);		//нужно ли здесь где-то обработчик ошибокю если нет,
}

int redirection_fd(t_redir *v_rdr)
{
	while (v_rdr)
	{
		if (v_rdr->type == OUT)
			redir_out(v_rdr);
		else if (v_rdr->type == INP)
			redir_inp(v_rdr);
		else if (v_rdr->type == APN)
			redir_apn(v_rdr);
		else if (v_rdr->type == HRD)
			redir_heredoc(v_rdr);
		v_rdr = v_rdr->next;
	}
	return (0);	//возможно где-то здесь нужен обработчик ошибок
}
