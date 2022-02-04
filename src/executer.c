/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/04 22:43:15 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
static int pipe_and_fork(void)
{
	return (0);
}
static space_pars(char *str)
{

}
*/

static void init_cmd_struct(t_cmd **cmds, char **str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (i + 1));
	cmds[i] = NULL;
	while (i)
	{
		cmds[--i] = (t_cmd *)malloc(sizeof(t_cmd));
		cmds[i]->cmd = str[i];
		cmds[i]->v_rdr = NULL;
	}
}

int executer(void)
{
	//представим, что подана строка "ls -al | wc -l"
	char *str[] = {"ls -al", "wc -l", NULL};
	t_cmd **cmds;

	cmds = NULL;
	init_cmd_struct(cmds, str);

	printf("%s\n", cmds[1]->cmd);
	return (0);
}
