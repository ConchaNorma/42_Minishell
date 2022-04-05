/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:45:20 by cnorma            #+#    #+#             */
/*   Updated: 2022/04/05 08:04:02 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>					//для вывода кода ошибок из errno
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>					//для переменных внутри функции open()

# include "../readline/readline.h"
# include "../readline/history.h"
# include "../libft/libft.h"
# include <signal.h>
# include <termios.h>

//global variable to specify the pid of the current process
pid_t		*g_pid;

//numbered list of commands for the error handler
typedef enum e_err{
	FR,
	ER,
	ERFR,
	ERFREX,
	FREX
}	t_err;

//numbered list of redirect types
typedef enum e_rtp{
	OUT,
	INP,
	APN,
	HRD
}	t_rtp;

//redirection list item
typedef struct s_redir{
	t_rtp			type;
	int				fd;
	char			*file;
	struct s_redir	*next;
}	t_redir;

//command list item
typedef struct s_cmd{
	t_redir			*v_rdr;
	int				cmd_num;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

//base structure
typedef struct s_exec
{
	char	**envp;
	char	*str;
	t_cmd	*cmds;
	pid_t	pid;
	pid_t	*pids;
	int		ofd[2];
	int		pfd[2];
	int		tfd[2];
	t_cmd	*tm_cmd;
	int		st;
	char	*path;
	int		exit_status;
}	t_exec;

/*
PREPARSER
*/

int		preparser(t_exec *vars);

/*
PARSER
*/
int		parser(t_exec *vars);
//parser of quote and slesh
void	ft_quote(t_exec *vars, int *i);
void	ft_bslesh(t_exec *vars, int *i);

//parser of dollar
void	ft_dollar_parse(t_exec *vars, int *i);

//parser of redirection
void	ft_backward_redir(t_exec *vars, int *i, int fd);
void	ft_forward_redir(t_exec *vars, int *i, int fd);
void	ft_digit(t_exec *vars, int *i);

//parser of pipes
void	ft_split_pipe(t_exec *vars, int *i);
//create command lines and pipes
void	ft_create_cmdmas(t_exec *vars, char *new_str);
t_cmd	*ft_create_cmds(void);
void	ft_create_cmdmas(t_exec *vars, char *new_str);


/*
EXECUTOR
*/

int		executer(t_exec *vars);
//redirection
int		redir_base(t_exec *vars);
int		redirection_fd(t_redir *v_rdr, int fd);
//built-ins
int		builtin_check_exec(t_exec *vars);
int		builtin_export(t_exec *vars, char **cmd);
int		builtin_unset(t_exec *vars, char **cmd);
int		builtin_pwd(void);
int		builtin_echo(char **cmd);
int		builtin_cd(char	*dir, t_exec *vars);
int		builtin_env(t_exec *vars);
void	builtin_exit(t_exec *vars, char **code);

/*
UTILS
*/

//signals
void	ft_signals(void);
//built-in-cd utils
void	chng_oldpwd(char **path, t_exec *vars);
char	*ft_cd_getpath(char	*dir, char **path);
//error & exit handling
int		ft_errfrex(t_exec *vars, t_err tp, int ex_st, char *err);
//error output
void	err_valid_id(t_exec *vars, char *str);
void	err_search_var(char **path, t_exec *vars, char *str);
void	put_err(t_exec *vars, char *str1, char *str2);
//cleaning
void	clean_base_struct(t_exec *vars, int ext);
//getting values from string or array
char	*get_path(char **envp, char *cmd);
char	*get_varname(char *var_str, int with_eq);
char	*get_varvalue(char *var_str);
//env-vars handling
int		find_repl_val_var_in_envp(char **envp, char *var);
int		srch_var_in_envp(char **envp, char *var_name);
int		add_var_in_envp(t_exec *vars, char *var);

#endif
