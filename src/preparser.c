/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:29:10 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/09 21:28:25 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*ft_preparser_bslesh(char *str, int *i)
{
	if (str[*i + 1] && (str[*i + 1] == '\"' || str[*i + 1] == '`'
			|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
		++(*i);
	return (0);
}

int	ft_preparser_dquote(char *str, int *i)
{
	while (str[++(*i)])
	{
		if (str[*i] =='\\' && (str[*i + 1] == '\"' || str[*i + 1] == '\\'))
			++(*i);
		else if (str[*i] == '\"')
			return (0);
	}
	return (printf("minishell: syntax error near unexpected token `\"\'\n"));
}

int	ft_preparser_squote(char *str, int *i)
{
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			return (0);
	}
	return (printf("minishell: syntax error near unexpected token `\'\'\n"));
}

int	ft_preparser_semicolon(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[j] == ';' && j - 1 == *i)
		return (printf("minishell: syntax error near unexpected token `;;\'\n"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] == ';')
		return (printf("minishell: syntax error near unexpected token `;;\'\n"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] != ';')
		return (printf("minishell: syntax error near unexpected token `;\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int	ft_preparser_pipe(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[j] == '|' && j - 1 == *i)
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] == ';')
		return (printf("minishell: syntax error near unexpected token `;;\'\n"));
	else if (j - 1 > *i && str[j] == ';' && str[j + 1] != ';')
		return (printf("minishell: syntax error near unexpected token `;\'\n"));
	else if (str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int	ft_preparser_redir_forward(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[j] == '>' && str[j + 1] == '>')
		return (printf("minishell: syntax error near unexpected token `>>\'\n"));
	else if (str[j] == '<' && str[j + 1] != '<')
		return (printf("minishell: syntax error near unexpected token `<\'\n"));
	else if (str[j] == '<' && str[j + 1] == '<')
		return (printf("minishell: syntax error near unexpected token `<<\'\n"));
	else if (j - 1 > *i && str[j] == '>' && str[j + 1] != '>')
		return (printf("minishell: syntax error near unexpected token `>\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int	ft_preparser_redir_backward(char *str, int *i)
{
	int	j;

	j = *i + 1;
	while (str[j] == ' ' && str[j])
		j++;
	if (str[j] == '<' && str[j + 1] == '<')
		return (printf("minishell: syntax error near unexpected token `<<\'\n"));
	else if (str[j] == '>' && str[j + 1] != '>')
		return (printf("minishell: syntax error near unexpected token `>\'\n"));
	else if (str[j] == '>' && str[j + 1] == '>')
		return (printf("minishell: syntax error near unexpected token `>>\'\n"));
	else if (j - 1 > *i && str[j] == '<' && str[j + 1] != '<')
		return (printf("minishell: syntax error near unexpected token `<\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] == '|')
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	else if (j - 1 > *i && str[j] == '|' && str[j + 1] != '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int	ft_preparser_str_end(char *str, int *i)
{
	int	j;

	j = *i;
	if (str[j] == '|')
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

int	ft_preparser_str_begin(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[j] == ' ')
		j++;
	if (str[j] == ';')
		return (printf("minishell: syntax error near unexpected token `;\'\n"));
	if (str[j] == '|')
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	*i = j;
	return (0);
}

int preparser(t_exec *vars)
{
	char	*prepars;
	int		i;

	prepars = ft_strdup(vars->str);
	i = -1;
	while (prepars[++i])
	{
		if (ft_preparser_str_end(prepars, &i))
			return (1);
		if (prepars[i] == '\'' && ft_preparser_squote(prepars, &i))
			return (1);
		else if (prepars[i] == '\\')
			ft_preparser_bslesh(prepars, &i);
		else if (prepars[i] == '\"' && ft_preparser_dquote(prepars, &i))
			return (1);
		else if (i == 0 && ft_preparser_str_begin(prepars, &i))
			return (1);
		else if (prepars[i] == ';' && ft_preparser_semicolon(prepars, &i))
			return (1);
		else if (prepars[i] == '|' && ft_preparser_pipe(prepars, &i))
			return (1);
		else if (prepars[i] == '>' && ft_preparser_redir_forward(prepars, &i))
			return (1);
		else if (prepars[i] == '<' && ft_preparser_redir_backward(prepars, &i))
			return (1);
	}
	printf("finish preparsing\n");
	return (0);
}
/* \- в конце, ||, |;, ;|, ; - в начале, | - в начале и в конце, ;;, >>>, <<<
*/
