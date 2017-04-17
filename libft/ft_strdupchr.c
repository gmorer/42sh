/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 15:55:38 by acottier          #+#    #+#             */
/*   Updated: 2017/04/15 10:56:47 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdupchr(char *s1, char c)
{
	char	*res;
	int		i;
	int		j;

	i = (int)ft_strlenchr((char*)s1, c);
	if (i == (int)ft_strlen((char *)s1))
		return (0);
	j = 0;
	if (!(res = ft_strnew(i + 1)))
		return (0);
	while (s1[j] != '\0' && s1[j] != c)
	{
		res[j] = s1[j];
		j++;
	}
	res[i] = '\0';
	return (res);
}
