/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:14:50 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/27 17:50:49 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	rl_replace_line (const char *text, int clear_undo)
{
	(void) text;
	(void) clear_undo;
	return ;
}

void ft_signal_ctrl_d(char *str)
{
	if (str == NULL)
	{
		printf("\033[1;36m\bMiMiShell >\033[0A");
		printf("\033[1;0m exit\n\033[0m");
		exit(EXIT_SUCCESS);
	}
}

void	signal_handler(int signal)
{
	(void) signal;
	//if (signal == SIGINT)
	//{
	//	printf("\n");
	//	printf("minishell>$");
	//}
	rl_on_new_line();
	rl_redisplay();
	printf("123\n");
	write(1, "  \b\b\n", 5);
	// печать строки из readline
	if (rl_on_new_line() == -1)
		exit(1);
	// вывод строки, которую мы ввели в командной строку
	rl_replace_line("", 1);
	// меняет то, что последнее было выведено
	rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, signal_handler); // CTRL + C
	signal(SIGQUIT, SIG_IGN);		// CTRL + /
}
