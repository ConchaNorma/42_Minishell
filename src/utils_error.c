/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 01:00:31 by aarnell           #+#    #+#             */
/*   Updated: 2022/04/04 01:06:12 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_valid_id(t_exec *vars, char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: export: `", str);
	tmp2 = ft_strjoin(tmp1, "': not a valid identifier");
	ft_putendl_fd(tmp2, 2);
	free(tmp1);
	free(tmp2);
	vars->exit_status = 1;
}

void	err_search_var(char **path, t_exec *vars, char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("minishell: cd: ", str);
	tmp2 = ft_strjoin(tmp1, " not set");
	ft_putendl_fd(tmp2, 2);
	free(tmp1);
	free(tmp2);
	free(*path);
	vars->exit_status = 1;
}

void	put_err(t_exec *vars, char *str1, char *str2)
{
	if (vars->exit_status != 258)
		str1 = ft_strjoin("minishell: ", vars->tm_cmd->cmd[0]);
	else
		str1 = ft_strjoin("minishell: syntax error near unexpected token ", \
				str2);
	if (vars->exit_status == 1)
	{
		str2 = ft_strjoin(str1, ": ");
		free(str1);
		str1 = str2;
		str2 = ft_strjoin(str1, vars->tm_cmd->cmd[1]);
		free(str1);
		str1 = str2;
	}
	if (vars->exit_status == 127)
	{
		str2 = ft_strjoin(str1, ": command not found");
		free(str1);
		str1 = str2;
	}
	if (vars->exit_status == 127 || vars->exit_status == 258)
		ft_putendl_fd(str1, 2);
	else
		perror(str1);
	free(str1);
}
