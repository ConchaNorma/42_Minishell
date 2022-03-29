/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/30 01:02:07 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_bslesh(t_exec *vars, int *i)
{
	char	*tmp;
	char	*tmp2;
	//char	*tmp3;

	tmp = ft_substr(vars->str, 0, *i);
	tmp2 = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
	free(vars->str);
	vars->str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
}

//char	*ft_bslesh(char *str, int *i)
//{
//	char	*tmp;
//	char	*tmp2;
//	char	*tmp3;

//	tmp3 = ft_substr(str, 0, *i);
//	tmp2 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
//	tmp = ft_strjoin(tmp3, tmp2);
//	free(tmp3);
//	free(tmp2);
//	return (tmp);
//}

static void	ft_dquote_sup(t_exec *vars, int *i)
{
	char	*tmp;

	while (vars->str[++(*i)])
	{
		if ((vars->str[*i] == '\\') && (vars->str[*i + 1] == '\"' \
		|| vars->str[*i + 1] == '`' || vars->str[*i + 1] == '$' \
		|| vars->str[*i + 1] == '\\'))
		{
			ft_bslesh(vars, i);
			//tmp = ft_bslesh(vars->str, i);
			//free(vars->str);
			//vars->str = tmp;
			++(*i);
		}
		if (vars->str[*i] == '$')
		{
			tmp = ft_dollar_parse(vars, i);
			free(vars->str);
			vars->str = tmp;
		}
		if (vars->str[*i] == '\"')
			break ;
	}
	//return (vars->str);
}

char	*ft_quote(t_exec *vars, int *i)
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
	tmp = ft_strjoin(tmp3, tmp2);
	*i -= 2;
	free (tmp2);
	free (tmp3);
	return (tmp);
}

char	*ft_space(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;

	j = *i - 1;
	while (vars->str[++j] == '\t')
		vars->str[j] = ' ';
	j = *i;
	if (*i == 0)
	{
		while (vars->str[++j] == ' ')
			;
		tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
	}
	else
	{
		while (vars->str[++j])
		{
			if (vars->str[j] != ' ' || !vars->str[j])
				break ;
		}
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
		tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - *i - 1);
	}
	*i = -1;
	return (tmp);
}

int	parser(t_exec *vars)
{
	int	i;

	vars->cmds = ft_create_cmds();
	i = -1;
	while (vars->str[++i])
	{
		if (vars->str[i] == '\'' || vars->str[i] == '\"')
			vars->str = ft_quote(vars, &i);
		else if (vars->str[i] == '\\')
			ft_bslesh(vars, &i);
			//vars->str = ft_bslesh(vars->str, &i);
		else if (vars->str[i] == '$')
			vars->str = ft_dollar_parse(vars, &i);
		else if (vars->str[i] == ' ' || vars->str[i] == '\t')
			vars->str = ft_space(vars, &i);
		else if (vars->str[i] == '>')
			vars->str = ft_forward_redir(vars, &i, 1);
		else if (vars->str[i] == '<')
			vars->str = ft_backward_redir(vars, &i, 0);
		else if (vars->str[i] == '|')
			vars->str = ft_split_pipe(vars, &i);
		else if (ft_isdigit(vars->str[i]))
			vars->str = ft_digit(vars, &i);
	}
	vars->str = ft_space(vars, &i);
	return (0);
}
