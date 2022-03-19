/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/18 08:24:32 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redir	*ft_create_redir(void)
{
	t_redir	*tmp;

	tmp = NULL;
	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		exit (1);
	//tmp->type = NULL;
	tmp->fd = -1;
	tmp->file = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_redir	*ft_redir_sup(t_cmd *tmp_cmds)
{
	t_redir	*tmp_redir;
	t_redir	*new;

	if (!tmp_cmds->v_rdr)
	{
		tmp_cmds->v_rdr = ft_create_redir();
		tmp_redir = tmp_cmds->v_rdr;
	}
	else
	{
		tmp_redir = tmp_cmds->v_rdr;
		new = ft_create_redir();
		while (tmp_redir->next)
			tmp_redir = tmp_redir->next;
		tmp_redir->next = new;
	}
	while (tmp_redir->next)
		tmp_redir = tmp_redir->next;
	return (tmp_redir);
}

char	*ft_forward_redir(t_exec *vars, int *i, int fd)
{
	int		j;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	char	*tmp;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	if (*i > 0)
	{
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
		//tmp = ft_substr(vars->str, *i, ft_strlen(vars->str) - *i - 1);
	}
	tmp_redir = ft_redir_sup(tmp_cmds);
	tmp_redir->type = OUT;
	if (vars->str[++(*i)] == '>')
	{
		tmp_redir->type = APN;
		++(*i);
	}
	tmp_redir->fd = fd;
	j = *i;
	tmp_redir->file = ft_file_parser(vars, &j);
	tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
	*i = -1;
	return (tmp);
}

char	*ft_backward_redir(t_exec *vars, int *i, int fd)
{
	int		j;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	char	*tmp;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	if (*i > 0)
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
	//vars->str = ft_space(vars, i);
	tmp_redir = ft_redir_sup(tmp_cmds);
	tmp_redir->type = INP;
	if (vars->str[++(*i)] == '<')
	{
		tmp_redir->type = HRD;
		++(*i);
	}
	tmp_redir->fd = fd;
	j = *i;
	tmp_redir->file = ft_file_parser(vars, &j, tmp_redir->type);
	tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
	*i = -1;
	return (tmp);
}
