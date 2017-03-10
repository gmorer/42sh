/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 15:18:50 by gmorer            #+#    #+#             */
/*   Updated: 2017/02/22 17:51:14 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmap(char **c)
{
	int y;

	if (!c)
		return ;
	y = 0;
	while (c[y])
	{
		ft_putstr(c[y]);
		ft_putchar('\n');
		ft_putendl("--------------------");
		y++;
	}
}