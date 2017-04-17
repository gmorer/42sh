/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:30:32 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:30:33 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		numlong(int i)
{
	int			rslt;

	rslt = 0;
	if (i == 0)
		return (1);
	if (i < 0)
		rslt++;
	while (i)
	{
		i = i / 10;
		rslt++;
	}
	return (rslt);
}

static char		*maxint(void)
{
	return ("2147483647");
}

char			*ft_itoa(int n)
{
	int			x;
	char		*c;
	int			sign;

	sign = 0;
	if (n < 0)
		sign = -1;
	x = numlong(n);
	if (n == 2147483647)
		return (maxint());
	if (!(c = (char*)malloc(sizeof(char) * (x + 1))))
		return (NULL);
	c[x] = '\0';
	x--;
	while (x >= 0)
	{
		c[x] = ft_abs(n % 10) + 48;
		n = n / 10;
		x--;
	}
	if (sign == -1)
		c[0] = '-';
	return (c);
}
