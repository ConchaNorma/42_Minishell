/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:18:59 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/05 13:31:18 by aarnell          ###   ########.fr       */
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

static t_cmd **init_cmd_struct(char **str)
{
	int i;
	t_cmd **cmds;

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
	return(cmds);
}

int executer(void)
{
	//представим, что подана строка "ls -al | wc -l"
	char *str[] = {"ls -al", "wc -l", NULL};
	t_cmd **cmds;
	cmds = init_cmd_struct(str);



	printf("%s\n", cmds[1]->cmd);
	return (0);
}
