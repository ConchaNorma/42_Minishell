/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/31 23:32:14 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_bslesh(t_exec *vars, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(vars->str, 0, *i);
	tmp2 = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
	free(vars->str);
	vars->str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}

static void	ft_dquote_sup(t_exec *vars, int *i)
{
	while (vars->str[++(*i)])
	{
		if ((vars->str[*i] == '\\') && (vars->str[*i + 1] == '\"' \
		|| vars->str[*i + 1] == '`' || vars->str[*i + 1] == '$' \
		|| vars->str[*i + 1] == '\\'))
		{
			ft_bslesh(vars, i);
			++(*i);
		}
		if (vars->str[*i] == '$')
			ft_dollar_parse(vars, i);
		if (vars->str[*i] == '\"')
			break ;
	}
}

void	ft_quote(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	if (vars->str[*i] == '\"')
		ft_dquote_sup(vars, i);
	else if (vars->str[*i] == '\'')
	{
		while (vars->str[++(*i)])
			if (vars->str[*i] == '\'')
				break ;
	}
	tmp = ft_substr(vars->str, 0, j);
	tmp2 = ft_substr(vars->str, j + 1, *i - j - 1);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp2 = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
	free(vars->str);
	vars->str = ft_strjoin(tmp3, tmp2);
	free (tmp2);
	free (tmp3);
	*i -= 2;
}

static void	ft_space(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;

	j = *i - 1;
	while (vars->str[++j] == '\t')
		vars->str[j] = ' ';
	j = *i;
	while (vars->str[++j] == ' ')
		;
	if (*i)
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
	tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
	*i = -1;
	free(vars->str);
	vars->str = tmp;
}

int	parser(t_exec *vars)
{
	int	i;

	vars->cmds = ft_create_cmds();
	i = -1;
	while (vars->str[++i])
	{
		if (vars->str[i] == '\'' || vars->str[i] == '\"')
			ft_quote(vars, &i);
		else if (vars->str[i] == '\\')
			ft_bslesh(vars, &i);
		else if (vars->str[i] == '$')
			ft_dollar_parse(vars, &i);
		else if (vars->str[i] == ' ' || vars->str[i] == '\t')
			ft_space(vars, &i);
		else if (vars->str[i] == '>')
			ft_forward_redir(vars, &i, 1);
		else if (vars->str[i] == '<')
			ft_backward_redir(vars, &i, 0);
		else if (vars->str[i] == '|')
			ft_split_pipe(vars, &i);
		else if (ft_isdigit(vars->str[i]))
			ft_digit(vars, &i);
	}
	ft_space(vars, &i);
	return (0);
}
