/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 10:12:49 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/29 10:30:17 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_options(char **argv)
{
	int i;

	i = 1;
	while (argv[i] && argv[i][0] == '-' && (argv[i][1] == 'n' || argv[i][1] ==
				'e') && argv[i][2] == '\0')
		i++;
	return (i);
}

int			ft_echo(char **argv)
{
	int		options;

	options = ft_echo_options(argv);
	while (argv[options])
	{
		ft_putstr(argv[options++]);
		if (argv[options])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
