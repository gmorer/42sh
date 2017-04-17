/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:31:40 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:31:41 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*x;
	char	*y;
	size_t	i;

	i = 0;
	x = malloc(size);
	y = (char*)x;
	if (size == 0)
		return (NULL);
	if (x == NULL)
		return (NULL);
	while (i < size)
	{
		y[i] = (char)0;
		i++;
	}
	return (x);
}
