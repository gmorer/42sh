/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:32:28 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:32:29 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*y;
	char	*z;

	i = 0;
	y = (char*)dst;
	z = (char*)src;
	if (n == 0)
		return (y);
	while (i <= n)
	{
		y[i] = z[i];
		i++;
	}
	return (y);
}
