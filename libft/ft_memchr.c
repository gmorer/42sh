/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:32:08 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:32:09 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*x;

	x = (unsigned char*)s;
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			if (x[i] == (unsigned char)c)
				return ((void*)&x[i]);
			i++;
		}
	}
	return (NULL);
}
