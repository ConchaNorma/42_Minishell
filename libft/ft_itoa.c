/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:17:54 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:17:56 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cntmem(int n)
{
	size_t	c;
	int		r;

	c = 0;
	r = n;
	while (r != 0)
	{
		r = r / 10;
		c++;
	}
	if (n <= 0)
		c++;
	return (c);
}

static void	ft_strfil(char *f, int n, size_t c)
{
	int	r;

	r = n;
	while (c-- > 0)
	{
		if (n < 0)
		{
			if (c == 0)
				f[c] = 45;
			else
				f[c] = r % 10 * (-1) + 48;
		}
		else
			f[c] = r % 10 + 48;
		r = r / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*f;
	size_t	c;

	c = ft_cntmem(n);
	f = (char *)malloc(sizeof(char) * (c + 1));
	if (f == NULL)
		return (NULL);
	ft_bzero(f, c + 1);
	ft_strfil(f, n, c);
	return (f);
}
