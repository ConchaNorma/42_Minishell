/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:45:20 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/19 20:40:53 by cnorma           ###   ########.fr       */
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

# define TMP_FILE "here_doc"

// Здесь будут структуры переменных для создания списков и деревьев
typedef enum e_tkn{
	NOTOKEN,
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	FILE_,
	WORD
}	t_tkn;

typedef enum e_rtp{
	OUT,
	INP,
	APN,
	HRD
}	t_rtp;

typedef struct s_redir{
	t_rtp			type;
	int				fd;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd{
	t_redir			*v_rdr;
	int				cmd_num;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**envp;
	char	*str;
	t_cmd	*cmds;
	pid_t	pid;
	t_list	*lvar;
	int		fd[2];
	int		st;
	char	*path;
	int		exit_status;

}	t_exec;


int		parser(t_exec *vars);
int		executer(t_exec *vars);
char	*ft_quote(char *str, int *i, char **envp);
//char	*ft_dquote(char *str, int *i, char **envp);
//char	*ft_squote(char *str, int *i);
char	*ft_bslesh(char *str, int *i);
char	*ft_dollar(char *str, int *i, char **envp);
void	ft_create_cmdmas(t_exec *vars, char *new_str);
int		preparser(t_exec *vars);
void	ft_exit(int err, char *str);
char	*get_path(char **envp, char *cmd);
int		redirection_fd(t_redir *v_rdr);

char	*get_varname(char *var_str, int with_eq);
char	*get_varvalue(char *var_str);
int		srch_var_in_envp(char **envp, char *var_name);

int		builtin_check(char **cmd, t_exec *vars);
int		builtin_export(t_exec *vars, char *var);
int		builtin_unset(t_exec *vars, char *var);
char	*builtin_pwd(int sgn);
int		builtin_cd(char *dir, char **envp);
void	builtin_env(char **envp);

void	signal_handler(int signal);
void	ft_signals(void);
void	ft_signal_ctrl_d(t_exec *vars);

char	*ft_readline(void);

#endif
