/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:30:14 by aarnell           #+#    #+#             */
/*   Updated: 2022/02/05 21:16:14 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_dquote(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = i;
	while (str[++i])
	{
		if (str[i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, i - j - 1);
	tmp3 = ft_substr(str, i + 1, ft_strlen(str) - i);
	tmp = ft_strjoin(ft_strjoin(tmp, tmp2), tmp3);
	free (tmp2);
	free (tmp3);
	return (tmp);
}

char	*ft_squote(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = i;
	while (str[++i])
	{
		if (str[i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, i - j - 1);
	tmp3 = ft_substr(str, i + 1, ft_strlen(str) - i);
	tmp = ft_strjoin(ft_strjoin(tmp, tmp2), tmp3);
	return (tmp);
}

//void *ft_split_pipes(char *str)
//{
//	t_pipeline	*pipes = NULL;
//	int			i;
//	int			ii;
//	int			j;
//	int			pipe_count;

//	i = -1;
//	ii = -1;
//	j = -1;
//	pipe_count = 0;
//	printf("1\n");
//	while (str[++i])
//		if (str[i] == '|')
//			pipe_count++;
//	pipes = (t_pipeline *)malloc(pipe_count * sizeof(t_pipeline));
//	i = -1;
//	while (str[++i])
//	{
//		printf("2\n");
//		if (str[i] == '|')
//		{
//			printf("3\n");
//			++ii;
//			//pipes->str[++j] =
//			pipes->str[++j] = ft_substr(str, ii, i - ii - 1);
//			printf("pipe0[%d]= %s\n", j, pipes->str[j]);
//			ii = ++i;
//		}
//	}
//	if (j == -1)
//		pipes->str[++j] = ft_substr(str, 0, i - 1);
//	pipes->str[++j] = NULL;
//	j = -1;
//	while (pipes->str[++j])
//		printf("pipe[%d]= %s\n", j, pipes->str[j]);
//	return (pipes);
//}


static void	ft_split_pipes_sup(t_pipeline	**pipes, char **tmp)
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
		pipes[i] = (t_pipeline *)malloc(sizeof(t_pipeline));
		len = ft_strlen(tmp[i]);
		while (tmp[i][start] == ' ')
			start++;
		while (tmp[i][len - 1] == ' ')
			len--;
		pipes[i]->str = ft_substr(tmp[i], start, len - start);
	}
}

t_pipeline **ft_split_pipes(char *str)
{
	t_pipeline	**pipes;
	char	**tmp;
	int		i;
	int		pipe_count;

	i = -1;
	pipe_count = 1;
	while (str[++i])
		if (str[i] == '|')
			pipe_count++;
	tmp = (char **)malloc(pipe_count * sizeof(char));
	tmp = ft_split(str, '|');
	pipes = (t_pipeline **)malloc((pipe_count + 1) * sizeof(t_pipeline *));
	pipes[pipe_count] = NULL;
	ft_split_pipes_sup(pipes, tmp);
	i = -1;
	while (tmp[++i])
		free (tmp[i]);
	free (tmp);
	i = -1;
	while (pipes[++i])
		printf("pipe[%d]= %s\n", i, pipes[i]->str);
	return (pipes);
}

/*
t_pipeline **ft_split_pipes(char *str)
{
	t_pipeline	**pipes;
	char	**tmp;
	int		len;
	int		start;
	int		i;
	int		pipe_count;

	i = -1;
	len = 0;
	start = 0;
	pipe_count = 1;
	while (str[++i])
		if (str[i] == '|')
			pipe_count++;
	tmp = (char **)malloc(pipe_count * sizeof(char));
	tmp = ft_split(str, '|');
	pipes = (t_pipeline **)malloc((pipe_count + 1) * sizeof(t_pipeline *));
	pipes[pipe_count] = NULL;
	i = -1;
	while (tmp[++i])
	{
		start = 0;
		pipes[i] = (t_pipeline *)malloc(sizeof(t_pipeline));
		len = ft_strlen(tmp[i]);
		while (tmp[i][start] == ' ')
			start++;
		while (tmp[i][len - 1] == ' ')
			len--;
		pipes[i]->str = ft_substr(tmp[i], start, len - start);
		free (tmp[i]);
	}
	free (tmp);
	i = -1;
	while (pipes[++i])
		printf("pipe[%d]= %s\n", i, pipes[i]->str);
	return (pipes);
}
*/

int parser(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_squote(str, i);
		if (str[i] == '\"')
			str = ft_dquote(str, i);
		if (str[i] == ' ')
			continue ;
		if (str[i] == '|')
			continue ;
		if (str[i] == '>')
			continue ;
		if (str[i] == '<')
			continue ;
		if (str[i] == '$')
			continue ;
	}
	printf("str_res= %s\n", str);
	ft_split_pipes(str);
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
