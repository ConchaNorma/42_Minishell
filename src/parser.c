/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/16 16:06:06 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_bslesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp = ft_strjoin(tmp, tmp2);
	(*i)++;
	return (tmp);
}

char	*ft_dquote(char *str, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] =='\\' && (str[*i + 1] == '\"' || str[*i + 1] == '`'
				|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = ft_bslesh(str, i);
		if (str[*i] == '$')
			ft_dollar(str, i, envp);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp = ft_strjoin(ft_strjoin(tmp, tmp2), tmp3);
	--(*i);
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

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp = ft_strjoin(ft_strjoin(tmp, tmp2), tmp3);
	--(*i);
	return (tmp);
}

char	*ft_dollar(char *str, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[j + 1] && (str[j + 1] == '_' || ft_isalnum(str[j + 1])))
		j++;
	if (j == *i)
		return (str);
	tmp = ft_substr(str, *i + 1, j - *i);
	tmp2 = ft_strjoin(tmp, "=");
	tmp3 = ft_strdup("");
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(tmp2, ft_substr(envp[j], 0, ft_strlen(tmp2)), \
			ft_strlen(tmp2)))
			tmp3 = ft_substr(envp[j], ft_strlen(tmp2), \
				ft_strlen(envp[j]) - ft_strlen(tmp2));
	}
	tmp2 = ft_substr(str, 0, *i);
	tmp = ft_strjoin(ft_strjoin(tmp2, tmp3), ft_substr(str, \
			*i + ft_strlen(tmp) + 1, ft_strlen(str) - (*i + ft_strlen(tmp))));
	*i += (1 + ft_strlen(tmp3));
	return (tmp);
}

char	*ft_space(char *str, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	tmp = ft_strdup(str);
	if (*i == 0)
	{
		while (str[++j] == ' ')
			;
		tmp = ft_substr(str, j, ft_strlen(str) - j);
	}
	else
	{
		while (str[++j])
		{
			if (str[j] != ' ' || !str[j])
				break ;
			tmp = ft_strjoin(ft_substr(str, 0, *i), \
				ft_substr(str, j, ft_strlen(str) - *i - 1));
		}
	}
	return (tmp);
}

char	*ft_tab(char *str, int *i)
{
	int		j;

	j = *i;
	while (str[j] == '\t')
	{
		str[j] = ' ';
		j++;
	}
	return (ft_space(str, i));
}

char *ft_file_parser(t_exec *vars, int *i)
{
	int		j;
	char	*tmp;

	if (vars->str[*i] == '>' || vars->str[*i] == '<')
		++(*i);
	while (vars->str[*i] == ' ' || vars->str[*i] == '\t')
		++(*i);
	j = *i;
	while (ft_isalnum(vars->str[*i]) || vars->str[*i] == '[' || vars->str[*i] == ']'\
		|| vars->str[*i] == '{' || vars->str[*i] == '}' || vars->str[*i] == '%' || vars->str[*i] == '@'\
		|| vars->str[*i] == '!' || vars->str[*i] == '.' || vars->str[*i] == '~' || vars->str[*i] == '='\
		|| vars->str[*i] == '+' || vars->str[*i] == '-' || vars->str[*i] == '_' || vars->str[*i] == '#'\
		|| vars->str[*i] == '^' || vars->str[*i] == '\"' || vars->str[*i] == '\'')
	{
		printf("str= %s\n", vars->str);
		printf("str= %c\n", vars->str[*i]);
		if (vars->str[*i] != '\"' && vars->str[*i] != '\'')
			++(*i);
		else {
			if (vars->str[*i] == '\"')
				vars->str = ft_dquote(vars->str, i, vars->envp);
			if (vars->str[*i] == '\'')
				vars->str = ft_squote(vars->str, i);
			printf("str= %s\n", vars->str);
		}
	}
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

char	*ft_forward_redir(t_exec *vars, int *i)
{
	int		j;
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;
	char	*tmp;

	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	tmp_redir = ft_redir_sup(tmp_cmds);
	tmp_redir->type = OUT;
	if (vars->str[++(*i)] == '>')
		tmp_redir->type = APN;
	j = *i;
	tmp_redir->file = ft_file_parser(vars, &j);
	printf("str= %s\n", vars->str);
	tmp = ft_strjoin(ft_substr(vars->str, 0, *i - 1),\
		ft_substr(vars->str, j, ft_strlen(vars->str) - j));
	printf("tmp_redir->type= %u\n", tmp_redir->type);
	printf("tmp_redir->file= %s\n", tmp_redir->file);
	printf("tmp= %s\n", tmp);
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

void	ft_create_cmdmas(t_exec *vars)
{
	t_cmd	*tmp_cmds;
	char	**tmp;
	int		i;

	i = 0;
	tmp_cmds = vars->cmds;
	while (tmp_cmds->next)
		tmp_cmds = tmp_cmds->next;
	if (tmp_cmds->cmd == NULL)
		tmp_cmds->cmd = (char **)malloc(sizeof(char *) * cmd_num);
	else
	{
		tmp = (char **)malloc(sizeof(char *) * ++cmd_num);
		while (i < cmd_num - 1)

	}

	printf("massive of cmd for execve\n");

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
	if (vars->str[len] == ' ')
			len--;
	tmp_cmds->cmd = ft_substr(vars->str, 0, len);
	tmp = ft_substr(vars->str, *i + 1, ft_strlen(vars->str) - *i);
	if (vars->str[*i])
	{
		new = ft_create_cmds();
		tmp_cmds->next = new;
	}

	printf("2\n");
	printf("str_0= %s\n", vars->str);
	printf("str_2= %s\n", tmp);
	printf("str_cmd= %s\n", vars->cmds->cmd);
	//vars->cmds = tmp_cmds;
	*i = -1;
	vars->st++;
	return (tmp);
}

int parser(t_exec *vars)
{
	int	i;
	t_cmd	*tmp_cmds;

	vars->cmds = ft_create_cmds();
	i = -1;
	while (vars->str[++i])
	{
		if (vars->str[i] == '\'')
			vars->str = ft_squote(vars->str, &i);
		if (vars->str[i] == '\\')
			vars->str = ft_bslesh(vars->str, &i);
		if (vars->str[i] == '\"')
			vars->str = ft_dquote(vars->str, &i, vars->envp);
		if (vars->str[i] == '$')
			vars->str = ft_dollar(vars->str, &i, vars->envp);
		if (vars->str[i] == ' ')
			vars->str = ft_space(vars->str, &i);
		if (vars->str[i] == '\t')
			vars->str = ft_tab(vars->str, &i);
		if (vars->str[i] == '>')
			vars->str = ft_forward_redir(vars, &i);
		if (vars->str[i] == '<')
			continue ;
		if (vars->str[i] == '|')
			vars->str = ft_split_pipe(vars, &i);
	}
	vars->str = ft_split_pipe(vars, &i);
	printf("str_res= %s\n", vars->str);

	//vars->cmds = ft_split_pipes(vars->str);
	//ft_split_pipes(vars);
	i = -1;
	tmp_cmds = vars->cmds;
	while (tmp_cmds)
	{
		printf("pipes[%d]= %s\n", ++i, tmp_cmds->cmd);
		tmp_cmds = tmp_cmds->next;
	}

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
