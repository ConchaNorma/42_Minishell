/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:45:20 by cnorma            #+#    #+#             */
/*   Updated: 2022/02/05 18:52:43 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
}	t_redir;

typedef struct s_cmd{
	t_redir	*v_rdr;
	char	*cmd;
}	t_cmd;

typedef struct s_pipeline{
	char	*str;
}	t_pipeline;

int parser(char *str);
int executer(void);

#endif
