/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:39:24 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:39:25 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*x;

	if (!(x = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		x[i] = f(s[i]);
		i++;
	}
	x[i] = '\0';
	return (x);
}
