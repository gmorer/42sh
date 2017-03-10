/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 10:12:49 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/07 13:27:29 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_echo_option(char **argv, char opt)
{
	int i;

	i = 1;
	while (argv[i] && argv[i][0] == '-' && (argv[i][1] == 'n' || argv[i][1] ==
				'e') && argv[i][2] == '\0')
	{
		if (argv[i][1] == opt)
			return (1);
		i++;
	}
	return (0);
}

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
	int		option_n;
	int		option_e;

	option_n = 0;
	option_e = 0;
	options = ft_echo_options(argv);
	if (options > 1)
	{
		option_n = ft_echo_option(argv, 'n');
		option_e = ft_echo_option(argv, 'e');
	}
	while (argv[options])
	{
		ft_putstr(argv[options++]);
		if (argv[options])
			ft_putchar(' ');
	}
	if (!option_n)
		ft_putchar('\n');
	(void)option_e;
	return (0);
}
