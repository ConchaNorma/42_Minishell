/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/08 22:25:48 by cnorma           ###   ########.fr       */
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

char	*ft_dquote(char *str, int *i)
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
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	tmp = ft_strjoin(ft_strjoin(tmp, tmp2), tmp3);
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
	return (tmp);
}

char	*ft_dollar(char *str, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[(j + 1)] == '_' || ft_isalnum(str[(j + 1)]))
		j++;
	if (j == *i)
		return (str);
	tmp = ft_substr(str, *i + 1, j - *i);
	tmp2 = ft_strjoin(tmp, "=");
	tmp3 = ft_strdup("");
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(tmp2, ft_substr(envp[j], 0, ft_strlen(tmp2)), ft_strlen(tmp2)))
			tmp3 = ft_substr(envp[j], ft_strlen(tmp2), ft_strlen(envp[j]) - ft_strlen(tmp2));;
	}
	tmp2 = ft_substr(str, 0, *i);
	tmp = ft_strjoin(ft_strjoin(tmp2, tmp3), ft_substr(str,
		*i + ft_strlen(tmp) + 1, ft_strlen(str) - (*i + ft_strlen(tmp))));
	*i += (1 +ft_strlen(tmp3));
	return (tmp);
}

static void	ft_split_pipes_sup(t_cmd **pipes, char **tmp)
{
	int		len;
	int		start;
	int		i;

	i = -1;
	len = 0;
	start = 0;
	i = -1;
	while (tmp[++i])
	{
		start = 0;
		pipes[i] = (t_cmd *)malloc(sizeof(t_cmd));
		len = ft_strlen(tmp[i]);
		while (tmp[i][start] == ' ')
			start++;
		while (tmp[i][len - 1] == ' ')
			len--;
		pipes[i]->cmd = ft_substr(tmp[i], start, len - start);
	}
}

static void ft_split_pipes(t_exec *vars)
{
	char	**tmp;
	int		i;
	int		pipe_count;

	i = -1;
	pipe_count = 1;
	while (vars->str[++i])
		if (vars->str[i] == '|')
			pipe_count++;
	vars->st = pipe_count;
	tmp = (char **)malloc(pipe_count * sizeof(char));
	tmp = ft_split(vars->str, '|');
	vars->cmds = (t_cmd **)malloc((pipe_count + 1) * sizeof(t_cmd *));
	vars->cmds[pipe_count] = NULL;
	ft_split_pipes_sup(vars->cmds, tmp);
	i = -1;
	while (tmp[++i])
		free (tmp[i]);
	free (tmp);
}

int parser(t_exec *vars)
{
	int	i;

	i = -1;
	while (vars->str[++i])
	{
		if (vars->str[i] == '\'')
			vars->str = ft_squote(vars->str, &i);
		if (vars->str[i] == '\\')
			vars->str = ft_bslesh(vars->str, &i);
		if (vars->str[i] == '\"')
			vars->str = ft_dquote(vars->str, &i);
		if (vars->str[i] == '$')
			vars->str = ft_dollar(vars->str, &i, vars->envp);
		if (vars->str[i] == ' ')
			continue ;
		if (vars->str[i] == '|')
			continue ;
		if (vars->str[i] == '>')
			continue ;
		if (vars->str[i] == '<')
			continue ;
		if (vars->str[i] == '$')
			continue ;
	}
	printf("str_res= %s\n", vars->str);
	//vars->cmds = ft_split_pipes(vars->str);
	ft_split_pipes(vars);
	i = -1;
	while (vars->cmds[++i])
		printf("pipes[%d]= %s\n", i, vars->cmds[i]->cmd);

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
