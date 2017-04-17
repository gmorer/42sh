/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:39:59 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:40:00 by rvievill         ###   ########.fr       */
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
