/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:29:10 by cnorma            #+#    #+#             */
/*   Updated: 2022/04/02 19:17:36 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_preparser_quote_bslesh(char *str, int *i, t_exec *vars)
{
	int	j;

	j = *i;
	if (str[*i] == '\\')
	{
		if (str[*i + 1] && (str[*i + 1] == '\"' || str[*i + 1] == '`'
				|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			++(*i);
		return (0);
	}
	while (str[++(*i)])
	{
		if (str[j] == '\"' && str[*i] == '\\' \
			&& (str[*i + 1] == '\"' || str[*i + 1] == '\\'))
			++(*i);
		else if ((str[j] == '\"' && str[*i] == '\"') \
				|| (str[j] == '\'' && str[*i] == '\''))
			return (0);
	}
	if (str[j] == '\"')
		return (ft_errfrex(vars, ER, 258, "`\"\'"));
	else if (str[j] == '\'')
		return (ft_errfrex(vars, ER, 258, "`\'\'"));
	return (0);
}

static int	ft_preparser_semi_pipe(char *str, int *i, t_exec *vars)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[*i] == ';' && str[j] == ';' && j - 1 == *i)
		return (ft_errfrex(vars, ER, 258, "`;;\'"));
	else if (str[*i] == '|' && str[j] == '|' && j - 1 == *i)
		return (ft_errfrex(vars, ER, 258, "`||\'"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] == ';')
		return (ft_errfrex(vars, ER, 258, "`;;\'"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] != ';')
		return (ft_errfrex(vars, ER, 258, "`;\'"));
	else if (str[*i] == ';' && str[j] == '|' && str[j + 1] == '|')
		return (ft_errfrex(vars, ER, 258, "`||\'"));
	else if (str[*i] == ';' && str[j] == '|' && str[j + 1] != '|')
		return (ft_errfrex(vars, ER, 258, "`|\'"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (ft_errfrex(vars, ER, 258, "`||\'"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (ft_errfrex(vars, ER, 258, "`|\'"));
	return (0);
}

static int	ft_preparser_redir(char *str, int *i, int j, t_exec *vars)
{
	while (str[j] == ' ' && str[j])
		j++;
	if (!str[j])
		return (ft_errfrex(vars, ER, 258, "`newline\'"));
	if (str[j] == '>' && str[j + 1] == '>')
		return (ft_errfrex(vars, ER, 258, "`>>\'"));
	else if (str[j] == '<' && str[j + 1] == '<')
		return (ft_errfrex(vars, ER, 258, "`<<|>>\'"));
	else if (str[*i] == '>' && str[j] == '<' && str[j + 1] != '<')
		return (ft_errfrex(vars, ER, 258, "`<|>\'"));
	else if (str[*i] == '<' && str[j] == '>' && str[j + 1] != '>')
		return (ft_errfrex(vars, ER, 258, "`>\'"));
	else if (str[*i] == '>' && j - 1 > *i && str[j] == '>' && str[j + 1] != '>')
		return (ft_errfrex(vars, ER, 258, "`>\'"));
	else if (str[*i] == '<' && j - 1 > *i && str[j] == '<' && str[j + 1] != '<')
		return (ft_errfrex(vars, ER, 258, "`<\'"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (ft_errfrex(vars, ER, 258, "`||\'"));
	else if (j - 1 == *i && str[j] == '|' && str[j + 1] == '|')
		return (ft_errfrex(vars, ER, 258, "`|\'"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (ft_errfrex(vars, ER, 258, "`|\'"));
	return (0);
}

static int	ft_preparser_str_beg_end(char *str, t_exec *vars)
{
	int		j;

	j = 0;
	while (str[j] == ' ')
		j++;
	if (str[j] == ';')
		return (ft_errfrex(vars, ER, 258, "`;\'"));
	else if (str[j] == '|')
		return (ft_errfrex(vars, ER, 258, "`|\'"));
	j = ft_strlen(str) - 1;
	while (str[j] == ' ')
		--j;
	if (str[j] == '|')
		return (ft_errfrex(vars, ER, 258, "`|\'"));
	return (0);
}

int	preparser(t_exec *vars)
{
	char	*prepars;
	int		i;

	prepars = vars->str;
	i = -1;
	while (prepars[++i])
	{
		if (i == 0 && ft_preparser_str_beg_end(prepars, vars))
			return (1);
		else if ((prepars[i] == '\'' || prepars[i] == '\"' \
			|| prepars[i] == '\\') \
			&& ft_preparser_quote_bslesh(prepars, &i, vars))
			return (1);
		else if ((prepars[i] == ';' || prepars[i] == '|') \
				&& ft_preparser_semi_pipe(prepars, &i, vars))
			return (1);
		else if ((prepars[i] == '>' || prepars[i] == '<') \
				&& ft_preparser_redir(prepars, &i, i + 1, vars))
			return (1);
	}
	return (0);
}
