/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/29 20:55:31 by cnorma           ###   ########.fr       */
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

void	ft_change_shlvl(t_exec *vars, int flag)
{
	char	*cur_shlvl;
	int		new_shlvl;
	char	*ex_shlvl;
	char	*tmp;
	int		ii;

	ii = srch_var_in_envp(vars->envp, "SHLVL");
	cur_shlvl = get_varvalue(vars->envp[ii]);
	new_shlvl = ft_atoi(cur_shlvl) + flag;
	tmp = ft_itoa(new_shlvl);
	ex_shlvl = ft_strjoin("SHLVL=", tmp);
	find_repl_val_var_in_envp(vars->envp, ex_shlvl);
	free (ex_shlvl);
	free (tmp);
}

void	ft_init_struct(t_exec *vars)
{
	vars->envp = NULL;
	vars->str = NULL;
	vars->path = NULL;
	vars->cmds = NULL;
	vars->tm_cmd = NULL;
	vars->pid = -1;
	vars->ofd[0] = -1;
	vars->ofd[1] = -1;
	vars->pfd[0] = -1;
	vars->pfd[1] = -1;
	vars->tfd[0] = -1;
	vars->tfd[1] = -1;
	vars->st = 1;
	vars->exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	//Нужно переменные занулять до выделения памяти, чтобы при очистке всех структур...
	//...в случае выхода по ошибке или стандартного, можно было очищать то, что выделено, и не очищать то, что не выделено
	t_exec	vars;
	//t_cmd	*tmp_cmds;
	//t_redir	*tmp_redir;
	//int		i;
	//int		i1;

	(void)argv;
	//i1 = -254;
	//(int)(unsigned char)i1;
	//printf("%d\n", i1);
	//инициализировать структуру или найти, где она инициализируется далее.
	//Возможно, инциализацию стоит сделать в начале бесконечного цикла ниже.
	if (argc != 1)
		return (printf("Wrong arguments\n"));
	ft_init_struct(&vars);
	g_pid = &vars.pid;
	vars.envp = ft_add_str_to_arr(envp, NULL); //почистить в конце
	//начать с нуля
	//увеличить переменную SHLVL
	//возможно при повторном запуске минишел, передать ей в переменную текущее envp или SHLVL

	// i = -1;
	//// while (vars.envp[++i])
	//while (++i < 33)
	//  	printf("vars.envp[%d] = %s\n", i, vars.envp[i]);
	switch_echoctl(0);
	//vars.st = 1;
	//дописать заполнение указателей структуры нулями, а также в структурах, где аллоцируется память
	//а затем написать функцию очистки структур с проходом по указателям
	//либо сделать структуру с указателями памяти для очистки, fd'шниками дл закрытия, и функцию гарбэйдж-коллектора

	//Вероятно тут будет бесконечный цикл, который будет завершаться exit'ом или ошибкой minishell
	vars.exit_status = 0;
	ft_change_shlvl(&vars, 1);

	while(1)
	{
		//Здесь нужен код, который будет слушать ввод, что-то там было про библиотеку readline
		ft_signals();
		vars.str = ft_readline();
		//ft_change_shlvl(&vars, 1);

		if (!vars.str || !ft_strlen(vars.str))
			continue ;

		//Здесь будет парсер
		if (preparser(&vars))
			continue ;
		vars.st = 1;
		parser(&vars);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
/*
		tmp_cmds = vars.cmds;
		while (tmp_cmds)
		{
			//printf("12\n");
			i = -1;
			while (++i < tmp_cmds->cmd_num)
				printf("pipes[%d-%d]= %s\n", 1, i, tmp_cmds->cmd[i]);
			if (tmp_cmds->v_rdr){
				tmp_redir = tmp_cmds->v_rdr;
				while(tmp_redir){
					//printf("13\n");
					printf("vars.cmds->v_rdr->type= %u\n", tmp_redir->type);
					printf("vars.cmds->v_rdr->fd= %d\n", tmp_redir->fd);
					printf("vars.cmds->v_rdr->file= %s\n", tmp_redir->file);
					tmp_redir = tmp_redir->next;
				}
			}
			tmp_cmds = tmp_cmds->next;
		}
		printf("finish parser\n");*/
		//write(1, "  \b\b\n", 5);
		free(vars.str);
		vars.str = NULL;
		//Здесь будет экзекютер
		if (vars.cmds->cmd && executer(&vars) == -1)
			ft_errfrex(&vars, ERFR, vars.exit_status, NULL);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
		else
			clean_base_struct(&vars, 0);
		//vars.exit_status = 0;
	}
	//Вероятно, тут должна быть очистка памяти и закрытие потоков в случае exit'а или ошибки
	//добавить изменине SHLVL
	//добавить изменение $_

	return (0);
}
