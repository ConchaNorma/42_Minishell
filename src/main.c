/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 22:50:02 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/24 21:43:36 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_arg(int argc, char **arg)
{
	(void)arg;
	if (argc < 1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (check_arg(argc, argv) != 0)
		return (printf("Wrong arguments\n"));
	printf("%s\n", readline("minishell$ " ));
	while (1)
		;
	return (0);
}
