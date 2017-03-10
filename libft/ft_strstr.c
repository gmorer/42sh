/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 17:56:55 by gmorer            #+#    #+#             */
/*   Updated: 2017/02/22 15:12:10 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	if (!s1 || !s2)
		return (NULL);
	if (s2[0] == '\0' || s1[0] == '\0')
		return (char*)(s1);
	while (s1[i] != '\0')
	{
		j = i;
		c = 0;
		while (s1[j] == s2[c])
		{
			j++;
			c++;
			if (s2[c] == '\0')
				return (char*)(&s1[i]);
		}
		i++;
	}
	return (NULL);
}
