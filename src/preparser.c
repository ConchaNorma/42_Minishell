/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:29:10 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/19 22:58:02 by aarnell          ###   ########.fr       */
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
		if (str[i] == '\'' && (!i || str[i - 1] != '\\')) {
			num++;
			while (str[++i])
			{
				if (str[i] == '\'') {
					num++;
					break ;
				}
			}
		}
	}
	//printf("num squote= %d\n", num);
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

int	ft_preparser_redir(char *str)
{
	int	i;
	int	num_f;
	int	num_b;

	i = -1;
	num_f = 0;
	num_b = 0;
	while (str[++i])
	{
		if (str[i] == '>')
			num_f++;
		if (str[i] == '<')
			num_b++;
		if (str[i] == ' ')
			continue ;
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ')
		{
			num_f = 0;
			num_b = 0;
		}
		if (num_f > 2 || num_b > 2 || (num_f + num_b) > 2)
			return (1);
	}
	return (0);
}

int preparser(t_exec *vars)
{
	if (ft_preparser_dquote(vars->str))
		//return (printf("minishell: syntax error near unexpected token `\"\'\n"));
		return (puterr_frexit(vars, ER, 258, "`\"\'"));
	if (ft_preparser_squote(vars->str))
		// return (printf("minishell: syntax error near unexpected token `\'\'\n"));
		return (puterr_frexit(vars, ER, 258, "`\'\'"));
	if (ft_preparser_semicolon_sup(vars->str))
		// return (printf("minishell: syntax error near unexpected token `;\'\n"));
		return (puterr_frexit(vars, ER, 258, "`;\'"));
	if (ft_preparser_dsemicolon(vars->str))
		// return (printf("minishell: syntax error near unexpected token `;;\'\n"));
		return (puterr_frexit(vars, ER, 258, "`;;\'"));
	if (ft_preparser_single_pipe(vars->str))
		// return (printf("minishell: syntax error near unexpected token `|\'\n"));
		return (puterr_frexit(vars, ER, 258, "`|\'"));
	if (ft_preparser_double_pipe(vars->str))
		// return (printf("minishell: syntax error near unexpected token `||\'\n"));
		return (puterr_frexit(vars, ER, 258, "`||\'"));
	if (ft_preparser_semicolon_pipe(vars->str))
		// return (printf("minishell: syntax error near unexpected token `|\'\n"));
		return (puterr_frexit(vars, ER, 258, "`|\'"));
	if (ft_preparser_pipe_semicolon(vars->str))
		// return (printf("minishell: syntax error near unexpected token `;\'\n"));
		return (puterr_frexit(vars, ER, 258, "`;\'"));
	if (ft_preparser_redir(vars->str))
		// return (printf("minishell: syntax error near unexpected token `> or `<\'\n"));
		return (puterr_frexit(vars, ER, 258, "`> or `<\'"));
	return (0);
}

/* \- в конце, ||, |;, ;|, ; - в начале, | - в начале и в конце, ;;, >>>, <<<
*/
