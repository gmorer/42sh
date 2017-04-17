/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:44:15 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:44:15 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*x;
	size_t	i;

	if (!(x = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = start;
	while (i < start + len)
	{
		x[i - start] = s[i];
		i++;
	}
	x[i - start] = '\0';
	return (x);
}
