/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:29:10 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/24 08:56:13 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_preparser_dquote(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			if (!i || str[i - 1] != '\\')
				num++;
	}
	if (num % 2)
		return (1);
	return (0);
}

int	ft_preparser_squote(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i])
	{
		if (str[i] == '\''){
			if (!i || str[i - 1] != '\\')
				num++;
		}
	}
	printf("num squote= %d\n", num);
	if (num % 2)
		return (1);
	return (0);
}

int	ft_preparser_semicolon_sup(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i] == ' ')
		;
	if (str[i] == ';')
		return (1);
	return (0);
}

int	ft_preparser_semicolon(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (*str == ' ')
		str++;
	if (*str == ';')
		return (1);
	while (*str)
	{
		if (*str == ';')
		{
			if (ft_preparser_semicolon_sup(str + 1))
				return (1);
		}
		str++;
	}
	return (0);
}

int	ft_preparser_dsemicolon(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i] == ' ')
		;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			num++;
		if (str[i] == ';' && str[i - 1] == ';' && num % 2 == 0)
			return (1);
	}
	return (0);
}

int	ft_preparser_single_pipe(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = ft_strlen(str);
	while (str[++i] == ' ')
		;
	while (str[--j] == ' ')
		;
	if (str[i] == '|' || str[j] == '|')
		return (1);
	return (0);
}

int	ft_preparser_double_pipe(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i] == ' ')
		;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			num++;
		if (str[i] == '|' && str[i - 1] == '|' && num % 2 == 0)
			return (1);
	}
	return (0);
}

int	ft_preparser_semicolon_pipe(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i] == ' ')
		;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			num++;
		if (str[i] == ';' && str[i - 1] == '|' && num % 2 == 0)
			return (1);
	}
	return (0);
}

int	ft_preparser_pipe_semicolon(char *str)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (str[++i] == ' ')
		;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			num++;
		if (str[i] == '|' && str[i - 1] == ';' && num % 2 == 0)
			return (1);
	}
	return (0);
}

int preparser(t_exec *vars)
{
	if (ft_preparser_dquote(vars->str))
		return (printf("minishell: syntax error near unexpected token `\"\'\n"));
	if (ft_preparser_squote(vars->str))
		return (printf("minishell: syntax error near unexpected token `\'\'\n"));
	if (ft_preparser_semicolon_sup(vars->str))
		return (printf("minishell: syntax error near unexpected token `;\'\n"));
	if (ft_preparser_dsemicolon(vars->str))
		return (printf("minishell: syntax error near unexpected token `;;\'\n"));
	if (ft_preparser_single_pipe(vars->str))
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	if (ft_preparser_double_pipe(vars->str))
		return (printf("minishell: syntax error near unexpected token `||\'\n"));
	if (ft_preparser_semicolon_pipe(vars->str))
		return (printf("minishell: syntax error near unexpected token `|\'\n"));
	if (ft_preparser_pipe_semicolon(vars->str))
		return (printf("minishell: syntax error near unexpected token `;\'\n"));
	return (0);
}

/* \- в конце, ||, |;, ;|, ; - в начале, | - в начале и в конце, ;;,
*/
