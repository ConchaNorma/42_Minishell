/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:28:34 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/20 18:32:16 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int redir_inp_out_apn(t_redir *v_rdr)
{
	int fd;
	int std;

	std = 1;
	if (v_rdr->type == INP)
	{
		fd = open(v_rdr->file, O_RDONLY, S_IREAD);		//дописать: при открытии нового, закрывать старый
		std = 0;
	}
	else if (v_rdr->type == OUT)
		fd = open(v_rdr->file, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD);
	else if (v_rdr->type == APN)
		fd = open(v_rdr->file, O_RDWR | O_CREAT | O_APPEND, S_IWRITE | S_IREAD);
	if (fd == -1)
		return (-1);
	dup2(fd, std);
	return (0);
	//как быть при перенаправлении на один STDIN/STDOUT/STDERR
}

static int redir_heredoc(t_redir *v_rdr)
{
	char *str;
	size_t len;
	int fd[2];
	char *res;
	char *tmp;

	if (pipe(fd) == -1)
		return (-1);
	res = NULL;
	tmp = NULL;
	while (1)
	{
		str = readline(">$ ");
		if (!str)
			continue ;
		len = ft_strlen(str);
		if(len < ft_strlen(v_rdr->file))
			len = ft_strlen(v_rdr->file);
		if(!ft_memcmp(str, v_rdr->file, len))
		{
			free(str);
			break ;
		}
		tmp = ft_strjoin(res, str);
		if (res)
			free(res);
		res = ft_strjoin(tmp, "\n");
		free(tmp);
		free(str);
	}
	len = 0;
	while (res[len])
		len++;
	write(fd[1], res, len);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	return (0);
}

int redirection_fd(t_redir *v_rdr)
{
	//дописать в редиректах открытие файла по пути типа /--/--/filename
	while (v_rdr)
	{
		if ((v_rdr->type == INP || v_rdr->type == OUT || \
			v_rdr->type == APN) && redir_inp_out_apn(v_rdr) == -1)
			return (-1);
		else if (v_rdr->type == HRD && redir_heredoc(v_rdr) == -1)
			return (-1);
		v_rdr = v_rdr->next;
	}
	return (0);
}
