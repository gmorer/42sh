/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:29:22 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/14 19:55:27 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freejoin(char const *s1, char const *s2)
{
	char	*x;
	int		j;
	char	*mabite;

	mabite = (char *)s1;
	if (!mabite && !s2)
		return (NULL);
	if (!s2)
		return (ft_strdup((char*)mabite));
	if (!mabite)
		return (ft_strdup((char*)s2));
	j = ft_strlen(mabite) + ft_strlen(s2) + 1;
	if (!(x = (char*)malloc(sizeof(char) * j)))
		return (NULL);
	ft_strcpy(x, mabite);
	ft_strcat(x, s2);
	ft_strdel(&mabite);
	return (x);
}
