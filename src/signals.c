/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/02/27 15:14:50 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/27 17:50:49 by cnorma           ###   ########.fr       */
=======
/*   Created: 2022/02/27 18:40:59 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/02 23:08:04 by cnorma           ###   ########.fr       */
>>>>>>> b9f0a88c4f88a6f0cb31ef47bb09023042890021
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

<<<<<<< HEAD
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
=======
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
void	ft_signal_ctrl_d(t_exec *vars)
{
	write(1, "exit", 4);
	//ft_putstr_fd("exit\n", 1);
	free(vars->str);
	//return(1);
}

void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
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
>>>>>>> b9f0a88c4f88a6f0cb31ef47bb09023042890021
}
