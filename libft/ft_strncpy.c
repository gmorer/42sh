/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:41:08 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:41:08 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t j;

	j = 0;
	while (j < n && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	while (j < n)
	{
		dst[j] = '\0';
		j++;
	}
	return (dst);
}
