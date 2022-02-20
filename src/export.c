/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:34:04 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/20 16:36:41 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 	ft_export(t_exec *vars)
{
	int		i;
	int		j;
	t_cmd	*tmp_cmds;

	tmp_cmds = vars->cmds;
	while (tmp_cmds)
	{
		i = -1;
		while (++i < tmp_cmds->cmd_num)
		{
			if (!ft_strncmp(tmp_cmds->cmd[i], "export", ft_strlen("export")))
			{
				j = i;
				while (++j < tmp_cmds->cmd_num)
				{
					if (ft_strrchr(tmp_cmds->cmd[j], '='))
						ft_addenv(tmp_cmds->cmd[j]);
				}
			}
		}

		tmp_cmds = tmp_cmds->next;
	}
}

int	ft_checkstr(char *str)
{
	int	i;

	i = 0;
	if (!ft_strrchr(str, '='))
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] != '=')
		if (str[++i] == ' ')
			return (1);
	return (0);
}

void 	ft_export_search(t_exec *vars)
{
	int		i;
	int		j;
	t_cmd	*tmp_cmds;

	tmp_cmds = vars->cmds;
	while (tmp_cmds)
	{
		i = 0;
		while (i < tmp_cmds->cmd_num && ft_strncmp(tmp_cmds->cmd[i], "export", ft_strlen("export"))
		{
			if (ft_checkstr(tmp_cmds->cmd[i]))
				return (1);
			++i;
		}
		if (i == tmp_cmds->cmd_num)
			return (1);
		while (++i < tmp_cmds->cmd_num)
		[
			if (ft_checkstr(tmp_cmds->cmd[i]))
				printf("minishell: export: `%s': not a valid identifier\n", tmp_cmds->cmd[i]);
			else
				ft_export(t_exec *vars, tmp_cmds->cmd[i]);
			i++;
		]


			while (!ft_strncmp(tmp_cmds->cmd[i], "export", ft_strlen("export"))
			if (ft_checkstr(tmp_cmds->cmd[i]))
				continue ;
			else if (!ft_strncmp(tmp_cmds->cmd[i], "export", ft_strlen("export")))
			{
				j = i;
				while (++j < tmp_cmds->cmd_num)
				{
					if (ft_strrchr(tmp_cmds->cmd[j], '='))
						ft_addenv(tmp_cmds->cmd[j]);
				}
			}
		}

		tmp_cmds = tmp_cmds->next;
	}
}
