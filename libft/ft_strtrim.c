/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 13:58:02 by gmorer            #+#    #+#             */
/*   Updated: 2017/02/17 20:33:40 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		space(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	size_t	i;
	char	*c;

	if (!(s))
		return (NULL);
	while (*s && space((unsigned char)*s))
		s++;
	i = ft_strlen(s);
	while (*s && space((unsigned char)s[--i]))
		;
	if (!(c = ft_strnew(i + 1)))
		return (NULL);
	c = ft_strncpy(c, s, i + 1);
	c[i + 1] = '\0';
	return (c);
}
