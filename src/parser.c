/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/16 19:51:26 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_bslesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp3 = ft_substr(str, 0, *i);
	tmp2 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp = ft_strjoin(tmp3, tmp2);
	free(tmp3);
	free(tmp2);
	return (tmp);
}

char	*ft_dquote_sup(char *str, int *i, char **envp)
{
	while (str[++(*i)])
	{
		if (str[*i] =='\\' && (str[*i + 1] == '\"' || str[*i + 1] == '`'
				|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
		{
			str = ft_bslesh(str, i);
			++(*i);
		}
		if (str[*i] == '$')
			str = ft_dollar(str, i, envp);
		if (str[*i] == '\"')
			break ;
	}
	return (str);
}

char	*ft_dquote(char *str, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	str = ft_dquote_sup(str, i, envp);
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp2 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp = ft_strjoin(tmp3, tmp2);
	*i -= 2;
	free (tmp2);
	free (tmp3);
	return (tmp);
}

char	*ft_squote(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	*i -= 2;
	return (tmp);
}

char	*ft_dollar(char *str, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	tmp3 = NULL;
	while (str[j + 1] && (str[j + 1] == '_' || ft_isalnum(str[j + 1])))
		j++;
	if (j == *i)
		return (str);
	tmp = ft_substr(str, *i + 1, j - *i);
	tmp2 = ft_strjoin(tmp, "=");
	j = ft_str_in_arrstr(envp, tmp2, ft_strlen(tmp2));
	if (j >= 0)
		tmp3 = ft_substr(envp[j], ft_strlen(tmp2), \
				ft_strlen(envp[j]) - ft_strlen(tmp2));
	else
		return (str);
		//tmp3 = ft_strdup("");
	tmp4 = ft_substr(str, 0, *i);
	free(tmp2);
	tmp2 = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	tmp4 = ft_substr(str, *i + ft_strlen(tmp) + 1, ft_strlen(str) - (*i + ft_strlen(tmp)));
	free(tmp);
	tmp = ft_strjoin(tmp2, tmp4);
	free(tmp2);
	free(tmp4);
	return (tmp);
}

char	*ft_space(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;

	j = *i - 1;
	while (vars->str[++j] == '\t')
		vars->str[j] = ' ';
	j = *i;
	if (*i == 0)
	{
		while (vars->str[++j] == ' ')
			;
		tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
	}
	else
	{
		while (vars->str[++j])
		{
			if (vars->str[j] != ' ' || !vars->str[j])
				break ;
		}
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
		tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - *i - 1);
	}
	*i = -1;
	return (tmp);
}
/*
char	*ft_tab(t_exec *vars, int *i)
{
	int		j;

	j = *i;
	while (vars->str[j] == '\t')
	{
		vars->str[j] = ' ';
		j++;
	}
	return (ft_space(vars, i));
}
*/
void	*ft_file_parser_check_str(t_exec *vars, int *i)
{
	if (vars->str[*i] == '$')
	{
		vars->str = ft_dollar(vars->str, i, vars->envp);
		++(*i);
	}
	else if (vars->str[*i] == '\\')
		vars->str = ft_bslesh(vars->str, i);
	else if (vars->str[*i] != '\"' && vars->str[*i] != '\'')
		++(*i);
	else
	{
		if (vars->str[*i] == '\"')
			vars->str = ft_dquote(vars->str, i, vars->envp);
		if (vars->str[*i] == '\'')
			vars->str = ft_squote(vars->str, i);
	}
	return (0);
}

char *ft_file_parser(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;
	char	*str_tmp;

	str_tmp = "{}[]%@.~=+-_#^\"\'$:\\>";
	while (vars->str[*i] == ' ' || vars->str[*i] == '\t')
		++(*i);
	j = *i;
	while (vars->str[*i] && (ft_isalnum(vars->str[*i]) || ft_strchr(str_tmp, vars->str[*i])))
		ft_file_parser_check_str(vars, i);
	tmp = NULL;
	tmp = ft_substr(vars->str, j, *i - j);
	return (tmp);
}

t_redir	*ft_create_redir(void)
{
	t_redir	*tmp;

	tmp = NULL;
	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		exit (1);
	//tmp->type = NULL;
	tmp->fd = -1;
	tmp->file = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_redir	*ft_redir_sup(t_cmd *tmp_cmds)
{
	t_redir	*tmp_redir;
	t_redir	*new;

	if (!tmp_cmds->v_rdr){
		tmp_cmds->v_rdr = ft_create_redir();
		tmp_redir = tmp_cmds->v_rdr;
	}
	else {
		tmp_redir = tmp_cmds->v_rdr;
		new = ft_create_redir();
		while (tmp_redir->next)
			tmp_redir = tmp_redir->next;
		tmp_redir->next = new;
	}
	while (tmp_redir->next)
		tmp_redir = tmp_redir->next;
	return (tmp_redir);
}

char	*ft_forward_redir(t_exec *vars, int *i, int fd)
{
	int		j;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	char	*tmp;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	if (*i > 0) {
		ft_create_cmdmas(vars, ft_substr(vars->str, 0, *i));
		tmp = ft_substr(vars->str, *i, ft_strlen(vars->str) - *i - 1);
	}
	//vars->str = ft_space(vars, i);
	tmp_redir = ft_redir_sup(tmp_cmds);
	tmp_redir->type = OUT;
	if (vars->str[++(*i)] == '>') {
		tmp_redir->type = APN;
		++(*i);
	}
	tmp_redir->fd = fd;
	j = *i;
	tmp_redir->file = ft_file_parser(vars, &j);
/*	printf("str= %s\n", vars->str);*/
/*	tmp = ft_strjoin(ft_substr(vars->str, 0, *i - 1),\
		ft_substr(vars->str, j, ft_strlen(vars->str) - j));
*/	tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
/*	printf("tmp_redir->type= %u\n", tmp_redir->type);
	printf("tmp_redir->file= %s\n", tmp_redir->file);
	printf("tmp= %s\n", tmp);*/
	*i = -1;
	return (tmp);
}

char	*ft_backward_redir(t_exec *vars, int *i, int fd)
{
	int		j;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	char	*tmp;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	vars->str = ft_space(vars, i);
	tmp_redir = ft_redir_sup(tmp_cmds);
	tmp_redir->type = INP;
	if (vars->str[++(*i)] == '<')
		tmp_redir->type = HRD;
	tmp_redir->fd = fd;
	j = *i;
	tmp_redir->file = ft_file_parser(vars, &j);
/*	printf("str= %s\n", vars->str);*/
/*	tmp = ft_strjoin(ft_substr(vars->str, 0, *i - 1),\
		ft_substr(vars->str, j, ft_strlen(vars->str) - j));
*/	tmp = ft_substr(vars->str, j, ft_strlen(vars->str) - j);
/*	printf("tmp_redir->type= %u\n", tmp_redir->type);
	printf("tmp_redir->file= %s\n", tmp_redir->file);
	printf("tmp= %s\n", tmp);*/
	*i = -1;
	return (tmp);
}

t_cmd	*ft_create_cmds(void)
{
	t_cmd	*tmp;

	tmp = NULL;
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		exit (1);
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
	return (str_mas);
}

void	ft_create_cmdmas(t_exec *vars, char *new_str)
{
	t_cmd	*tmp_cmds;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	tmp_cmds->cmd = ft_str_newline(tmp_cmds->cmd, new_str, ++(tmp_cmds->cmd_num));
}

char *ft_split_pipe(t_exec *vars, int *i)
{
	char	*tmp;
	t_cmd	*new;
	t_cmd	*tmp_cmds;
	int		len;

	len = *i;
	tmp_cmds = vars->cmds;
	//if (vars->str[*i + 1] == '|')
	//	exit(1);
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	tmp = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
	if (vars->str[*i])
	{
		new = ft_create_cmds();
		tmp_cmds->next = new;
	}
	*i = -1;
	vars->st++;
	return (tmp);
}

char	*ft_digit(t_exec *vars, int *i)
{
	int		j;
	int		end_digit;
	char	*tmp;
	int		fd;

	j = *i;
	tmp = ft_strdup(vars->str);
	while (ft_isdigit(vars->str[++j]))
		;
	end_digit = j;
	while (vars->str[j] == ' ')
		j++;
	fd = ft_atoi(ft_substr(vars->str, *i, end_digit));
	if (vars->str[j] == '>')
		tmp = ft_forward_redir(vars, &j, fd);
	else if (vars->str[j] == '<')
		tmp = ft_backward_redir(vars, &j, fd);
	else
		return (tmp);
	*i = -1;
	return (tmp);
}

int parser(t_exec *vars)
{
	int		i;
	vars->cmds = ft_create_cmds();
	i = -1;
	while (vars->str[++i])
	{
		if (vars->str[i] == '\'')
			vars->str = ft_squote(vars->str, &i);
		else if (vars->str[i] == '\\')
			vars->str = ft_bslesh(vars->str, &i);
		else if (vars->str[i] == '\"')
			vars->str = ft_dquote(vars->str, &i, vars->envp);
		else if (vars->str[i] == '$')
			vars->str = ft_dollar(vars->str, &i, vars->envp);
		else if (vars->str[i] == ' ' || vars->str[i] == '\t')
			vars->str = ft_space(vars, &i);
		//else if (vars->str[i] == '\t')
		//	vars->str = ft_tab(vars, &i);
		else if (vars->str[i] == '>')
			vars->str = ft_forward_redir(vars, &i, 1);
		else if (vars->str[i] == '<')
			vars->str = ft_backward_redir(vars, &i, 0);
		else if (vars->str[i] == '|')
			vars->str = ft_split_pipe(vars, &i);
		else if (ft_isdigit(vars->str[i]))
			vars->str = ft_digit(vars, &i);
	}
	vars->str = ft_space(vars, &i);
	i = -1;
	return (0);
	//получить строку и порезать/разложить по элементам - перенос строки, пайпы, разделители, команды, флаги, аргументы/файлы
	//склеить по переносу "\"
	//порезать по пайпам "|"
	//порезать по разделителям ";", "&&", "||"

	//здесь же прописать проверки на некорректные символы, команды.
	//(возможно, какие-то случаи или типы проверок лучше проводить в экзекютере)
}
//Вопросы-мысли по парсеру:
// - Как shell работает с разделителями и пайпами?
//		Какой приоритет?
// - Учесть экранирование \ "" '' и перенос строки "\"
// - Учесть обработку переменных и работу {} для переменных
// - Учесть ассинхронное выполнение команд, предшествующих &
// - Учесть группировку команд {}
// - Учесть вызов отдельного экземпляра shell при использовании ()
// - Учесть обработку кавычек ' '' " `  в разных сочетаниях, закрытых-незакрытых
// - Учесть обработку *, ?, []
// - Учесть закрытие каналов стандартных ввода и вывода <& >&
// - Где лучше писать историю вызванных команд? Сразу записывать из парсера куда-то, или до?
// - Учесть работу с перенаправлениями ввода-вывода < << >> >
// - Особое внимание уделить <<
//		Где принимать ввод текста? В парсере или в экзекютере?
