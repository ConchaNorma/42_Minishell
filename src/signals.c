/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:40:59 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/30 20:59:57 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (*g_pid > 0)
			ft_putstr_fd("^C", 1);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (*g_pid < 1)
			rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		if (*g_pid > 0)
			ft_putstr_fd("^\\Quit: 3\n", 1);
		rl_on_new_line();
		if (*g_pid < 1)
			rl_redisplay();
	}
}

void	ft_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
