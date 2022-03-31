/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:47:38 by cnorma            #+#    #+#             */
/*   Updated: 2022/03/31 00:38:59 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*ft_create_cmds(void)
{
	t_cmd	*tmp;

	tmp = NULL;
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
	{
		perror("minishell: ");
		exit (1);
	}
	tmp->v_rdr = NULL;
	tmp->cmd_num = 1;
	tmp->cmd = NULL;
	tmp->next = NULL;
	return (tmp);
}

char	**ft_str_newline(char **str_mas, char *new_str, int str_num)
{
	char	**tmp;
	int		i;

	i = 0;
	if (str_mas == NULL)
		str_mas = (char **)malloc(sizeof(char *) * str_num);
	else
	{
		tmp = (char **)malloc(sizeof(char *) * str_num);
		i = -1;
		while (++i < str_num - 2)
			tmp[i] = str_mas[i];
		free (str_mas);
		str_mas = tmp;
	}
	str_mas[i] = ft_strdup(new_str);
	str_mas[i + 1] = NULL;
	free(new_str);
	return (str_mas);
}

void	ft_create_cmdmas(t_exec *vars, char *new_str)
{
	t_cmd	*tmp_cmds;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	tmp_cmds->cmd = ft_str_newline(tmp_cmds->cmd, \
			new_str, ++(tmp_cmds->cmd_num));
}

void	ft_split_pipe(t_exec *vars, int *i)
{
	char	*tmp;
	t_cmd	*new;
	t_cmd	*tmp_cmds;
	int		len;

	len = *i;
	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	//tmp = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
	if (*i)
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
		//tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
	tmp = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i - 1);
	//else
	//{
	//	tmp = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i - 1);
	//}

	//if (vars->str[*i])
	//{
		new = ft_create_cmds();
		tmp_cmds->next = new;
	//}
	*i = -1;
	vars->st++;
	free(vars->str);
	vars->str = tmp;
}

//char	*ft_split_pipe(t_exec *vars, int *i)
//{
//	char	*tmp;
//	t_cmd	*new;
//	t_cmd	*tmp_cmds;
//	int		len;

//	len = *i;
//	tmp_cmds = vars->cmds;
//	while (tmp_cmds->next)
//		tmp_cmds = tmp_cmds->next;
//	tmp = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
//	if (vars->str[*i])
//	{
//		new = ft_create_cmds();
//		tmp_cmds->next = new;
//	}
//	*i = -1;
//	vars->st++;
//	return (tmp);
//}

void	ft_digit(t_exec *vars, int *i)
{
	int		j;
	int		end_digit;
	char	*tmp;
	int		fd;

	j = *i;
	//tmp = ft_strdup(vars->str);
	while (ft_isdigit(vars->str[++j]))
		;
	end_digit = j;
	while (vars->str[j] == ' ')
		j++;
	tmp = ft_substr(vars->str, *i, end_digit);
	fd = ft_atoi(tmp);
	free(tmp);
	if (vars->str[j] == '>' || vars->str[j] == '<')
		*i = -1;
	if (vars->str[j] == '>')
		ft_forward_redir(vars, &j, fd);
		//tmp = ft_forward_redir(vars, &j, fd);
	else if (vars->str[j] == '<')
		ft_backward_redir(vars, &j, fd);
		//tmp = ft_backward_redir(vars, &j, fd);
	//else
	//	return (tmp);
	//return (tmp);
}

//char	*ft_digit(t_exec *vars, int *i)
//{
//	int		j;
//	int		end_digit;
//	char	*tmp;
//	int		fd;

//	j = *i;
//	tmp = ft_strdup(vars->str);
//	while (ft_isdigit(vars->str[++j]))
//		;
//	end_digit = j;
//	while (vars->str[j] == ' ')
//		j++;
//	fd = ft_atoi(ft_substr(vars->str, *i, end_digit));
//	if (vars->str[j] == '>')
//		ft_forward_redir(vars, &j, fd);
//		//tmp = ft_forward_redir(vars, &j, fd);
//	else if (vars->str[j] == '<')
//		tmp = ft_backward_redir(vars, &j, fd);
//	else
//		return (tmp);
//	*i = -1;
//	return (tmp);
//}
