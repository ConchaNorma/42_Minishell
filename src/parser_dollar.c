/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:34:34 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/31 21:30:20 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_dollar_free(char **tmp, int size)
{
	int	ii;

	ii = -1;
	while (++ii < size)
		free(tmp[ii]);
	free(tmp);
}

void	ft_dollar_question(t_exec *vars, int *i)
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
	//return (tmp);
}

//char	*ft_dollar_question(char *str, int *i, t_exec *vars)
//{
//	int		j;
//	char	*tmp;
//	char	*tmp1;
//	char	*tmp2;

//	j = *i + 1;
//	tmp = ft_substr(str, 0, *i);
//	tmp1 = ft_itoa (vars->exit_status);
//	tmp2 = ft_strjoin(tmp, tmp1);
//	free (tmp);
//	free (tmp1);
//	tmp1 = ft_substr(str, j + 1, ft_strlen(str) - j);
//	tmp = ft_strjoin(tmp2, tmp1);
//	free (tmp1);
//	free (tmp2);
//	return (tmp);
//}

void	ft_dollar(t_exec *vars, int *i)
{
	int		j;
	int		k;
	//char	*tmp;
	char	*tmp1;
	char	**tmp2;

	j = *i;
	while (vars->str[j + 1] && (vars->str[j + 1] == '_' || ft_isalnum(vars->str[j + 1])))
		j++;
	if (j == *i)
		return ;
	tmp1 = ft_substr(vars->str, *i + 1, j - *i);
	k = srch_var_in_envp(vars->envp, tmp1);
	if (k < 0)
	{
		free(tmp1);
		return ;
	}
	free(tmp1);
	tmp2 = (char **)malloc(sizeof(char *) * 6);
	tmp2[0] = ft_substr(vars->str, *i + 1, j - *i);
	//k = srch_var_in_envp(envp, tmp2[0]);
	//if (k < 0)
	//{
	//	ft_frmtrx(tmp2);
	//	return (str);
	//}
	tmp2[1] = ft_strdup(get_varvalue(vars->envp[k]));
	tmp2[2] = ft_substr(vars->str, 0, *i);
	tmp2[3] = ft_strjoin(tmp2[2], tmp2[1]);
	tmp2[4] = ft_substr(vars->str, j + 1, ft_strlen(vars->str) - j);
	tmp2[5] = NULL;
	free(vars->str);
	vars->str = ft_strjoin(tmp2[3], tmp2[4]);
	ft_frmtrx(tmp2);
	//ft_dollar_free(tmp2, 5);
	//return (tmp);
}

//char	*ft_dollar(char *str, int *i, char **envp)
//{
//	int		j;
//	int		k;
//	char	*tmp;
//	char	*tmp1;
//	char	**tmp2;

//	j = *i;
//	while (str[j + 1] && (str[j + 1] == '_' || ft_isalnum(str[j + 1])))
//		j++;
//	if (j == *i)
//		return (str);
//	tmp1 = ft_substr(str, *i + 1, j - *i);
//	k = srch_var_in_envp(envp, tmp1);
//	if (k < 0)
//	{
//		free(tmp1);
//		return (str);
//	}
//	free(tmp1);
//	tmp2 = (char **)malloc(sizeof(char *) * 6);
//	tmp2[0] = ft_substr(str, *i + 1, j - *i);
//	//k = srch_var_in_envp(envp, tmp2[0]);
//	//if (k < 0)
//	//{
//	//	ft_frmtrx(tmp2);
//	//	return (str);
//	//}
//	tmp2[1] = ft_strdup(get_varvalue(envp[k]));
//	tmp2[2] = ft_substr(str, 0, *i);
//	tmp2[3] = ft_strjoin(tmp2[2], tmp2[1]);
//	tmp2[4] = ft_substr(str, j + 1, ft_strlen(str) - j);
//	tmp2[5] = NULL;
//	tmp = ft_strjoin(tmp2[3], tmp2[4]);
//	ft_frmtrx(tmp2);
//	//ft_dollar_free(tmp2, 5);
//	return (tmp);
//}

void	ft_dollar_parse(t_exec *vars, int *i)
{
	//char	*tmp;

	if (vars->str[*i + 1] == '?')
		ft_dollar_question(vars, i);
		//tmp = ft_dollar_question(vars->str, i, vars);
	else
		ft_dollar(vars, i);
	//	tmp = ft_dollar(vars->str, i, vars->envp);
	//free(vars->str);
	//vars->str = ft_strdup(tmp);
	//if (tmp)
	//	free(tmp);
}

//char	*ft_dollar_parse(t_exec *vars, int *i)
//{
//	char	*tmp;

//	if (vars->str[*i + 1] == '?')
//		tmp = ft_dollar_question(vars->str, i, vars);
//	else
//		tmp = ft_dollar(vars->str, i, vars->envp);
//	return (tmp);
//}
