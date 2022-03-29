/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:39:46 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/29 20:21:09 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_file_parser(t_exec *vars, int *i, t_rtp type)
{
	int		j;
	char	*tmp;

	while (vars->str[*i] == ' ' || vars->str[*i] == '\t')
		++(*i);
	j = *i;
	while (vars->str[*i] && !ft_strchr(" |<>;()", vars->str[*i]))
	{
		if (vars->str[*i] == '$' && type != HRD)
			vars->str = ft_dollar_parse(vars, i);
		else if (vars->str[*i] == '\\')
			vars->str = ft_bslesh(vars->str, i);
		else if (vars->str[*i] == '\"' || vars->str[*i] == '\'')
			vars->str = ft_quote(vars, i);
		(*i)++;
	}
	tmp = NULL;
	tmp = ft_substr(vars->str, j, *i - j);
	return (tmp);
}

t_redir	*ft_create_redir(void)
{
	t_redir	*tmp;

	tmp = NULL;
	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		exit (1);
	tmp->type = 0;
	tmp->fd = -1;
	tmp->file = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_redir	*ft_redir_new(t_cmd *tmp_cmds)
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
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
	tmp_redir = ft_redir_new(tmp_cmds);
	tmp_redir->type = OUT;
	if (vars->str[++(*i)] == '>')
	{
		tmp_redir->type = APN;
		++(*i);
	}
	tmp_redir->fd = fd;
	j = *i;
	tmp_redir->file = ft_file_parser(vars, &j, tmp_redir->type);
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
	tmp_redir = ft_redir_new(tmp_cmds);
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
