/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:29:10 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/15 21:12:31 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_preparser_quote_bslesh(char *str, int *i)
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
		if (str[j] == '\"' && str[*i] =='\\' \
			&& (str[*i + 1] == '\"' || str[*i + 1] == '\\'))
			++(*i);
		else if ((str[j] == '\"' && str[*i] == '\"') \
				|| (str[j] == '\'' && str[*i] == '\''))
			return (0);
	}
	return (printf("minishell: syntax error near unexpected token `%c\'\n", \
			str[j]));
}

int	ft_preparser_semi_pipe(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[*i] == ';' && str[j] == ';' && j - 1 == *i)
		return (printf("minishell: syntax error near unexpected token `;;\'\n"));
	else if (str[*i] == '|' && str[j] == '|' && j - 1 == *i)
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] == ';')
		return (printf("minishell: syntax error near unexpected token `;;\'\n"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] != ';')
		return (printf("minishell: syntax error near unexpected token `;\'\n"));
	else if (str[*i] == ';' && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (str[*i] == ';' && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int	ft_preparser_redir(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[j] == '>' && str[j + 1] == '>')
		return (printf("minishell: syntax error near unexpected token `>>\'\n"));
	else if (str[j] == '<' && str[j + 1] == '<')
		return (printf("minishell: syntax error near unexpected token `<<\'\n"));
	else if (str[*i] == '>' && str[j] == '<' && str[j + 1] != '<')
		return (printf("minishell: syntax error near unexpected token `<\'\n"));
	else if (str[*i] == '<' && str[j] == '>' && str[j + 1] != '>')
		return (printf("minishell: syntax error near unexpected token `>\'\n"));
	else if (str[*i] == '>' && j - 1 > *i && str[j] == '>' && str[j + 1] != '>')
		return (printf("minishell: syntax error near unexpected token `>\'\n"));
	else if (str[*i] == '<' && j - 1 > *i && str[j] == '<' && str[j + 1] != '<')
		return (printf("minishell: syntax error near unexpected token `<\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 == *i && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int	ft_preparser_str_beg_end(char *str, int *i)
{
	int	j;

	j = *i;
	if (*i == 0)
	{
		while (str[j] == ' ')
			j++;
		if (str[j] == ';' || str[j] == '|')
			return \
				(printf("minishell: syntax error near unexpected token `%c\'\n", \
					str[j]));
		*i = j;
	}
	else if (str[j] == '|')
	{
		while (str[++j])
		{
			if (str[j] != ' ')
				return (0);
		}
		return (printf("minishell: syntax error near unexpected token `%c\'\n", \
				str[*i]));
	}
	return (0);
}

int	preparser(t_exec *vars)
{
	char	*prepars;
	int		i;

	prepars = ft_strdup(vars->str);
	i = -1;
	while (prepars[++i])
	{
		if (ft_preparser_str_beg_end(prepars, &i))
			return (1);
		if ((prepars[i] == '\'' || prepars[i] == '\"') \
			&& ft_preparser_quote_bslesh(prepars, &i))
			return (1);
		else if (prepars[i] == '\\')
			ft_preparser_quote_bslesh(prepars, &i);
		else if ((prepars[i] == ';' || prepars[i] == '|') \
				&& ft_preparser_semi_pipe(prepars, &i))
			return (1);
		else if ((prepars[i] == '>' || prepars[i] == '<') \
				&& ft_preparser_redir(prepars, &i))
			return (1);
	}
	printf("finish preparsing\n");
	return (0);
}
