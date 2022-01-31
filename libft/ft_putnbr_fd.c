/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:19:19 by aarnell           #+#    #+#             */
/*   Updated: 2021/08/31 22:19:22 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	k;

	k = (unsigned int) n;
	if (n < 0)
	{
		ft_putchar_fd(45, fd);
		k = (unsigned int) n * (-1);
	}
	if (k >= 10)
		ft_putnbr_fd((k / 10), fd);
	ft_putchar_fd((k % 10 + 48), fd);
}
