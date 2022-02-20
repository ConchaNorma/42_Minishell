/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:45:20 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/20 20:29:27 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
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

}	t_exec;

typedef struct s_pipeline{
	char	*cmd;
}	t_pipeline;

int		parser(t_exec *vars);
int		executer(t_exec *vars);
char	*ft_dquote(char *str, int *i, char **envp);
char	*ft_squote(char *str, int *i);
char	*ft_bslesh(char *str, int *i);
char	*ft_dollar(char *str, int *i, char **envp);
void	ft_create_cmdmas(t_exec *vars, char *new_str);
int		preparser(t_exec *vars);

#endif
