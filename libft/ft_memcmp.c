/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:32:17 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:32:18 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*x;
	unsigned char	*y;

	x = (unsigned char*)s1;
	y = (unsigned char*)s2;
	i = 0;
	if (s2 == NULL && s1 == NULL)
		return (0);
	while (n--)
	{
		if (x[i] != y[i])
			return (x[i] - y[i]);
		i++;
	}
	return (0);
}
