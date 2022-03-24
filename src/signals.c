/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:40:59 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/24 22:17:44 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
void	rl_replace_line (const char *text, int clear_undo)
{
  int len;

  len = strlen (text);
  if (len >= rl_line_buffer_len)
    rl_extend_line_buffer (len);
  strcpy (rl_line_buffer, text);
  rl_end = len;

  if (clear_undo)
    rl_free_undo_list ();

  _rl_fix_point (1);
}
*/
/*
void rl_replace_line (const char *text, int clear_undo)
{
	printf("%s", text);
	(void) clear_undo;
	return ;
}
*/
/*
void	ft_signal_ctrl_d(t_exec *vars)
{
	ft_putstr_fd("\033[11C", 1);
	ft_putstr_fd("\x1bM\x1b[`exit\n", 1);
	//write(1, "exit", 4);
	//ft_putstr_fd("exit\n", 0);
	//free(vars->str);
	//return(1);
}
*/
void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	//if (rl_on_new_line() == -1) // печать строки из readline
	//    exit(1);
	//rl_replace_line("", 1); // вывод строки, которую мы ввели в командной строку
	//rl_redisplay();         // меняет то, что последнее было выведено
}

void ft_signals(void)
{
	signal(SIGINT, signal_handler); // CTRL + C
	signal(SIGQUIT, SIG_IGN);    // CTRL + /
}
