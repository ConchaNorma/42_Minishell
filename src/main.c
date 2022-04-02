/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/04/02 21:04:00 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	switch_echoctl(char on)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (on)
		ts.c_lflag |= ECHOCTL;
	else
		ts.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &ts);
}

static char	*ft_readline(void)
{
	char	*input;

	//input = readline("minishell>$ ");
	input = readline("");
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

static void	ft_change_shlvl(t_exec *vars, int flag)
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

static void	ft_init_struct(t_exec *vars, char **envp)
{
	g_pid = &vars->pid;
	vars->envp = ft_add_str_to_arr(envp, NULL);
	vars->str = NULL;
	vars->path = NULL;
	vars->cmds = NULL;
	vars->tm_cmd = NULL;
	vars->pid = -1;
	vars->pids = NULL;
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
	t_exec	vars;

	(void)argv;
	if (argc != 1)
		return (printf("Wrong arguments\n"));
	ft_init_struct(&vars, envp);
	switch_echoctl(0);
	ft_change_shlvl(&vars, 1);
	while (1)
	{
		ft_signals();
		vars.str = ft_readline();
		if (!vars.str || !ft_strlen(vars.str))
			continue ;
		if (preparser(&vars))
			continue ;
		parser(&vars);
		if (vars.cmds->cmd && executer(&vars) == -1)
			ft_errfrex(&vars, ERFR, vars.exit_status, NULL);
		else
			clean_base_struct(&vars, 0);
	}
	return (0);
}
