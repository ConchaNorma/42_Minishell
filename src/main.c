/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/23 17:01:31 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_exec vars;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	int		i;

	if (argc != 1)
		return (printf("Wrong arguments\n"));
	vars.envp = ft_add_str_to_arr(envp, NULL); //почистить в конце
	// i = -1;
	// while (vars.envp[++i])
	//  	printf("vars.envp[%d] = %s\n", i, vars.envp[i]);
	vars.st = 1;
	//дописать заполнение указателей структуры нулями, а также в структурах, где аллоцируется память
	//а затем написать функцию очистки структур с проходом по указателям
	//либо сделать структуру с указателями памяти для очистки, fd'шниками дл закрытия, и функцию гарбэйдж-коллектора

	//Вероятно тут будет бесконечный цикл, который будет завершаться exit'ом или ошибкой minishell
	while(1)
	{
		//Здесь нужен код, который будет слушать ввод, что-то там было про библиотеку readline
		vars.str = NULL;
		vars.str = readline("minishell>$ ");
		//printf("%s\n", vars.str);

		//Здесь будет парсер
		if (preparser(&vars))
			return (1);
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

		free(vars.str);

		//Здесь будет экзекютер
		//executer(&vars);	//Возможно, стоит добавить возврат ошибки для выхода из бесконечного цикла
		//builtin_env(vars.envp);
		// printf("11\n");
		//break ; //Убрать, когда будет написан код, слушающий ввод строки
	}
/*	printf("1");*/
/*	 tmp_cmds = vars.cmds;
	 while (tmp_cmds)
	 {
	 	i = -1;
	 	printf("cmd_num= %d\n", tmp_cmds->cmd_num);
	 	while (++i < tmp_cmds->cmd_num)
	 		printf("pipes= %s\n", tmp_cmds->cmd[i]);
	 	if (tmp_cmds->v_rdr)
	 	{
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
*/
	//Вероятно, тут должна быть очистка памяти и закрытие потоков в случае exit'а или ошибки
	return (0);
}
