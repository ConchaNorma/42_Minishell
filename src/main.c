/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/20 22:54:57 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(int argc, char **arg)
{
	if (argc < 1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;

	if (check_arg(argc, argv) != 0)
		return (printf("Wrong arguments\n"));
	printf ("Hello Minishell>\n");
	return (0);
}
