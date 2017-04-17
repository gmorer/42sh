/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:32:47 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:32:48 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmpdst;
	const unsigned char	*tmpsrc;

	tmpsrc = src;
	tmpdst = dst;
	if (len)
	{
		if (dst > src)
		{
			tmpdst += len;
			tmpsrc += len;
			while (len--)
				*--tmpdst = *--tmpsrc;
		}
		else
		{
			while (len--)
				*tmpdst++ = *tmpsrc++;
		}
	}
	return (dst);
}
