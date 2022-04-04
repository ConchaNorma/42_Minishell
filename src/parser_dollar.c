/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:34:34 by cnorma            #+#    #+#             */
/*   Updated: 2022/04/04 08:10:39 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_dollar_question(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	j = *i + 1;
	tmp = ft_substr(vars->str, 0, *i);
	tmp1 = ft_itoa (vars->exit_status);
	tmp2 = ft_strjoin(tmp, tmp1);
	free (tmp);
	free (tmp1);
	tmp1 = ft_substr(vars->str, j + 1, ft_strlen(vars->str) - j);
	free(vars->str);
	vars->str = ft_strjoin(tmp2, tmp1);
	free (tmp1);
	free (tmp2);
}

static int	ft_dollar_word_lenth(t_exec *vars, int *i)
{
	int	j;

	j = *i;
	while (vars->str[j + 1] && (vars->str[j + 1] == '_' \
			|| ft_isalnum(vars->str[j + 1])))
		j++;
	return (j);
}

static void	ft_dollar(t_exec *vars, int *i)
{
	int		j;
	int		k;
	char	**tmp2;

	j = ft_dollar_word_lenth(vars, i);
	if (j == *i)
		return ;
	tmp2 = (char **)malloc(sizeof(char *) * 6);
	tmp2[0] = ft_substr(vars->str, *i + 1, j - *i);
	k = srch_var_in_envp(vars->envp, tmp2[0]);
	if (k < 0)
		//tmp2[1] = ft_strdup("");
		tmp2[1] = NULL;
	else
		tmp2[1] = ft_strdup(get_varvalue(vars->envp[k]));
	tmp2[2] = ft_substr(vars->str, 0, *i);
	tmp2[3] = ft_strjoin(tmp2[2], tmp2[1]);
	tmp2[4] = ft_substr(vars->str, j + 1, ft_strlen(vars->str) - j);
	tmp2[5] = NULL;
	free(vars->str);
	vars->str = ft_strjoin(tmp2[3], tmp2[4]);
	ft_frmtrx(tmp2);
	//i--;
}

void	ft_dollar_parse(t_exec *vars, int *i)
{
	if (vars->str[*i + 1] == '?')
		ft_dollar_question(vars, i);
	else
		ft_dollar(vars, i);
	--i;
}
