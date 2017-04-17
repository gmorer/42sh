/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:38:42 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:38:43 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;
	size_t		lengt;

	d = dst;
	s = src;
	n = size;
	while (n-- != 0 && *d != '\0')
		d++;
	lengt = d - dst;
	n = size - lengt;
	if (n == 0)
		return (lengt + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (lengt + (s - src));
}
