/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/03/19 20:18:16 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*ft_split_pipe(t_exec *vars, int *i)
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
	int	i;

	vars->cmds = ft_create_cmds();
	i = -1;
	while (vars->str[++i])
	{
		if (vars->str[i] == '\'' || vars->str[i] == '\"')
			vars->str = ft_quote(vars->str, &i, vars->envp);
		else if (vars->str[i] == '\\')
			vars->str = ft_bslesh(vars->str, &i);
		else if (vars->str[i] == '$')
			vars->str = ft_dollar(vars->str, &i, vars->envp);
		else if (vars->str[i] == ' ' || vars->str[i] == '\t')
			vars->str = ft_space(vars, &i);
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
}
	//получить строку и порезать/разложить по элементам - перенос строки, пайпы, разделители, команды, флаги, аргументы/файлы
	//склеить по переносу "\"
	//порезать по пайпам "|"
	//порезать по разделителям ";", "&&", "||"

	//здесь же прописать проверки на некорректные символы, команды.
	//(возможно, какие-то случаи или типы проверок лучше проводить в экзекютере)
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
