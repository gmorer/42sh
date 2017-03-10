/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:37:04 by acottier          #+#    #+#             */
/*   Updated: 2016/11/15 20:00:37 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, int n)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && n > 0)
	{
		if (s[i] == (char)c)
			return ((char*)&s[i]);
		i++;
		n--;
	}
	if ((char)c == '\0')
		return ((char*)&s[i]);
	return (0);
}
