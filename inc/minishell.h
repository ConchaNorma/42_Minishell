/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:45:20 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/09 19:39:21 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

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
	t_rtp	type;
	int		fd;
	char	*file;
}	t_redir;

typedef struct s_cmd{
	t_redir	**v_rdr;
	char	*cmd;
}	t_cmd;

typedef struct s_exec
{
	char	**envp;
	char	*str;
	t_cmd	**cmds;
	pid_t	pid;
	int		fd[2];
	int		st;
	char	**cmd;
	char	*path;

}	t_exec;


void	ft_exit(int err, char *str);
char	*get_path(char **envp, char *cmd);
int		redirection_fd(t_exec *vars);
int		parser(t_exec *vars);
int		executer(t_exec *vars);

#endif
