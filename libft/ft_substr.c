/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:22:05 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:22:07 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	l;

	if (!s)
		return (NULL);
	if ((size_t) start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	l = ft_strlen((char *)(s + start));
	if (l > len)
		l = len;
	buf = (char *)malloc(sizeof(char) * l + 1);
	if (buf)
	{
		ft_strlcpy(buf, (s + start), l + 1);
		return (buf);
	}
	return (NULL);
}
