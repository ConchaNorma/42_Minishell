/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/04 21:38:16 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	switch_echoctl(char on)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (on)
		ts.c_lflag |= ECHOCTL;
	else
		ts.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

char	*ft_readline(void)
{
	char	*input;

	input = readline("minishell>$ ");
	if (!input)
	{
		printf(" exit\n");
		exit(-1);
	}
	else if (*input == '\0')
		free(input);
	else
		add_history(input);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	vars;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	int		i;

	(void)argv;
	if (argc != 1)
		return (printf("Wrong arguments\n"));
	vars.envp = ft_add_str_to_arr(envp, NULL); //почистить в конце

	// i = -1;
	// while (vars.envp[++i])
	//  	printf("vars.envp[%d] = %s\n", i, vars.envp[i]);
	switch_echoctl(0);
	//vars.st = 1;
	//дописать заполнение указателей структуры нулями, а также в структурах, где аллоцируется память
	//а затем написать функцию очистки структур с проходом по указателям
	//либо сделать структуру с указателями памяти для очистки, fd'шниками дл закрытия, и функцию гарбэйдж-коллектора

	//Вероятно тут будет бесконечный цикл, который будет завершаться exit'ом или ошибкой minishell
	//ft_signals();
	//ft_signals();
	while(1)
	{
		//Здесь нужен код, который будет слушать ввод, что-то там было про библиотеку readline
		ft_signals();
		vars.str = NULL;
		//vars.str = readline("minishell>$ ");
		vars.str = ft_readline();
		//signal(SIGINT, &signal_handler);
		//signal(SIGQUIT, SIG_IGN);
		//if (!vars.str)
		//	ft_signal_ctrl_d(&vars);

		//if (!vars.str)
		//{
		//	ft_putstr_fd("\033[11C", 1);
		//	ft_putstr_fd("\x1bM\x1b[`exit\n", 1);
		//	//write(1, "exit", 4);
		//	//ft_putstr_fd("exit\n", 0);
		//	free(vars.str);
		//	return(1);
		//}
		if (!vars.str)
			continue;
		//printf("%s\n", vars.str);

		//Здесь будет парсер
		if (preparser(&vars))
			return (1);
		vars.st = 1;
		parser(&vars);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
/*		printf("vars.str1= %s\n", vars.str);*/

		tmp_cmds = vars.cmds;
		while (tmp_cmds)
		{
			printf("12\n");
			i = -1;
			while (++i < tmp_cmds->cmd_num)
				printf("pipes[%d-%d]= %s\n", 1, i, tmp_cmds->cmd[i]);
			if (tmp_cmds->v_rdr){
				tmp_redir = tmp_cmds->v_rdr;
				while(tmp_redir){
					printf("13\n");
					printf("vars.cmds->v_rdr->type= %u\n", tmp_redir->type);
					printf("vars.cmds->v_rdr->fd= %d\n", tmp_redir->fd);
					printf("vars.cmds->v_rdr->file= %s\n", tmp_redir->file);
					tmp_redir = tmp_redir->next;
				}
			}
			tmp_cmds = tmp_cmds->next;
		}
		printf("2222\n");
		write(1, "  \b\b\n", 5);
		free(vars.str);

		//Здесь будет экзекютер
		//executer(&vars);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
		//builtin_env(vars.envp);
		// printf("11\n");
		//break ; //Убрать, когда будет написан код, слушающий ввод строки
	}
	//Вероятно, тут должна быть очистка памяти и закрытие потоков в случае exit'а или ошибки
	return (0);
}
