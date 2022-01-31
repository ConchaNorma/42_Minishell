/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:19:38 by aarnell           #+#    #+#             */
/*   Updated: 2022/01/31 22:57:55 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fr(char **str, int j)
{
	while (--j + 1)
		free(str[j]);
	free(str);
	return (-1);
}

static int	ft_mlfl(char **str, char const *s, int *j, int n)
{
	int	i;
	int	k;
	int	sz;

	i = *j;
	k = 0;
	sz = 0;
	str[i] = malloc(sizeof(char) * (n + 1));
	if (!str[i])
		return (ft_fr(str, i));
	while (k++ <= n)
	{
		if (k - 1 == n)
			str[i][k - 1] = '\0';
		else
			str[i][k - 1] = s[sz++];
	}
	*j = i + 1;
	return (sz);
}

static int	ft_malfil(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	n;
	int	size;

	i = 0;
	j = 0;
	n = 0;
	size = 0;
	while (s[i] || n > 0)
	{
		if (s[i] && s[i++] != c)
		{
			if (n++ == 0)
				size = i - 1;
		}
		else if (n > 0)
		{
			size = size + ft_mlfl(str, (s + size), &j, n);
			if (size == -1)
				return (size);
			n = 0;
		}
	}
	return (j);
}

static int	ft_cntsz(char const *s, char c)
{
	int	sz;
	int	i;
	int	n;

	sz = 0;
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i++] != c)
			n++;
		else if (n > 0)
		{
			n = 0;
			sz++;
		}
	}
	if (n > 0)
		sz++;
	return (sz);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		size;

	size = 0;
	if (!s)
		return (0);
	size = ft_cntsz(s, c);
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (0);
	size = ft_malfil(str, s, c);
	if (size == -1)
		return (0);
	str[size] = 0;
	return (str);
}
